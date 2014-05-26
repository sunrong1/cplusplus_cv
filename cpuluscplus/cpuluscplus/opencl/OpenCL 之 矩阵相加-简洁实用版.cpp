#include <iostream>
#include <fstream>
#include <sstream>
#include <CL/cl.h>
cl_command_queue CreateCommandQueue(cl_context &context, cl_device_id &device);
cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName);
bool CreateMemObjects(cl_context context, cl_mem memObjects[3],float *a, float *b);
void Cleanup(cl_context context, cl_command_queue commandQueue,cl_program program, cl_kernel kernel, cl_mem memObjects[3]);
inline void checkErr(cl_int err, const char * name);
const int ARRAY_SIZE = 1000;
//  Create memory objects used as the arguments to the kernel
bool CreateMemObjects(cl_context context, cl_mem memObjects[3],float *a, float *b)
{
	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * ARRAY_SIZE, a, NULL);
	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(float) * ARRAY_SIZE, b, NULL);
	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(float) * ARRAY_SIZE, NULL, NULL);

	if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL)
	{
		std::cerr << "Error creating memory objects." << std::endl;
		return false;
	}

	return true;
}
int main(int argc, char** argv)
{
	cl_context context = 0;
	cl_command_queue commandQueue = 0;
	cl_program program = 0;
	cl_device_id device = 0;
	cl_kernel kernel = 0;
	cl_mem memObjects[3] = { 0, 0, 0 };
	cl_int errNum;

	commandQueue = CreateCommandQueue(context, device);
	program = CreateProgram(context, device, "sun.cl");
	kernel = clCreateKernel(program, "hello_kernel", NULL);

	if (commandQueue == NULL || program == NULL || kernel == NULL)
	{
		std::cerr << "Error create kernel objects." << std::endl;
		return false;
	}
	// Create memory objects that will be used as arguments to kernel. 
	float result[ARRAY_SIZE];
	float a[ARRAY_SIZE];
	float b[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		a[i] = (float)i;
		b[i] = (float)(i * 2);
	}
	
	if (!CreateMemObjects(context, memObjects, a, b))  //在设备上创建buffer对象
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

	// Set the kernel arguments (result, a, b)
	errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
	errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
	errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);
	checkErr(errNum, "clSetKernelArg");

	size_t globalWorkSize[1] = { ARRAY_SIZE };
	size_t localWorkSize[1] = { 1 };

	// Queue the kernel up for execution -----opencl runtime 维度：1
	errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
		globalWorkSize, localWorkSize,
		0, NULL, NULL);
	checkErr(errNum, "clEnqueueNDRangeKernel");

	// Read the output buffer back to the Host
	errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE,
		0, ARRAY_SIZE * sizeof(float), result,
		0, NULL, NULL);
	checkErr(errNum, "clEnqueueReadBuffer");

	// Output the result buffer
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Executed program succesfully." << std::endl;
	Cleanup(context, commandQueue, program, kernel, memObjects);

	return 0;
}

cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName)
{
	cl_int errNum;
	cl_program program;

	std::ifstream kernelFile(fileName, std::ios::in);
	if (!kernelFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << fileName << std::endl;
		return NULL;
	}

	std::ostringstream oss;
	oss << kernelFile.rdbuf();

	std::string srcStdStr = oss.str();
	const char *srcStr = srcStdStr.c_str();
	program = clCreateProgramWithSource(context, 1,
		(const char**)&srcStr,
		NULL, &errNum);
	checkErr(errNum, "clCreateProgramWithSource");
	//在多个支持OpenCL的设备上编译程序对象，设备个数：0，所有与program相关的设备上
	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL); 
	if (errNum != CL_SUCCESS)
	{
		// Determine the reason for the error
		char buildLog[16384];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
			sizeof(buildLog), buildLog, NULL);

		std::cerr << "Error in kernel: " << std::endl;
		std::cerr << buildLog;
		clReleaseProgram(program);
		return NULL;
	}

	return program;
}

//  Create a command queue on the first device available on the context
cl_command_queue CreateCommandQueue(cl_context &context, cl_device_id &device)
{
	cl_int errNum;
	cl_uint numPlatforms;
	cl_platform_id * platformIDs;
	cl_uint numDevices;
	cl_device_id * deviceIDs;
	cl_command_queue commandQueue = NULL;


	// First, select an OpenCL platform to run on. 
	errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
	platformIDs = (cl_platform_id *)alloca(sizeof(cl_platform_id) * numPlatforms);
	errNum = clGetPlatformIDs(numPlatforms, platformIDs, NULL);
	if (errNum != CL_SUCCESS || numPlatforms <= 0)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return NULL;
	}
	else std::cout<<"number of platforms:"<<numPlatforms<<std::endl;

	deviceIDs = NULL;
	errNum = clGetDeviceIDs(
		platformIDs[0], 
		CL_DEVICE_TYPE_GPU, //寻找GPU device 的个数
		0,
		NULL,
		&numDevices);
	if (errNum != CL_SUCCESS && errNum != CL_DEVICE_NOT_FOUND)
	{
		checkErr(errNum, "clGetDeviceIDs");
	}
	else std::cout<<"number of devices:"<<numDevices<<std::endl;
	deviceIDs = (cl_device_id *)alloca(sizeof(cl_device_id) * numDevices);
	errNum = clGetDeviceIDs(
		platformIDs[0],
		CL_DEVICE_TYPE_GPU,
		numDevices, 
		&deviceIDs[0], 
		NULL);
	checkErr(errNum, "clGetDeviceIDs");
	// Next, create an OpenCL context on the platform.  Attempt to
	// create a GPU-based context, and if that fails, try to create
	// a CPU-based context.
	cl_context_properties contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)platformIDs[0],
		0
	};
	/*context = clCreateContext(
		contextProperties, 
		numDevices,
		deviceIDs, 
		NULL,
		NULL, 
		&errNum);
	checkErr(errNum, "clCreateContext");*/
	//如果有平台和设备类型，可以使用clCreateContextFromType()创建上下文。上下文较随意，可以包含不同设备类型
	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU,NULL, NULL, &errNum);
	if (errNum != CL_SUCCESS)
	{
		std::cout << "Could not create GPU context, trying CPU..." << std::endl;
		context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
			NULL, NULL, &errNum);
		if (errNum != CL_SUCCESS)
		{
			std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
			return NULL;
		}
	}

	// In this example, we just choose the first available device.  In a
	// real program, you would likely use all available devices or choose
	// the highest performance device based on OpenCL device queries  // 在一个设备上建立命令队列
	commandQueue = clCreateCommandQueue(context, deviceIDs[0], 0, &errNum);
	checkErr(errNum, "clCreateCommandQueue");
	device=deviceIDs[0];
	return commandQueue;
}
void Cleanup(cl_context context, cl_command_queue commandQueue,
	cl_program program, cl_kernel kernel, cl_mem memObjects[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (memObjects[i] != 0)
			clReleaseMemObject(memObjects[i]);
	}
	if (commandQueue != 0)
		clReleaseCommandQueue(commandQueue);

	if (kernel != 0)
		clReleaseKernel(kernel);

	if (program != 0)
		clReleaseProgram(program);

	if (context != 0)
		clReleaseContext(context);

}
inline void checkErr(cl_int err, const char * name)
{
	if (err != CL_SUCCESS) {
		std::cerr << "ERROR: " <<  name << " (" << err << ")" << std::endl;
		exit(EXIT_FAILURE);
	}
}
