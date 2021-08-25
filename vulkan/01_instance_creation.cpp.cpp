//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//// stdexcept 和 iostream 头包含用于报告和传播错误。
//#include <iostream>
//#include <stdexcept>
//// cstdlib 报头提供了 EXIT_SUCCESS 和 EXIT_FAILURE 的宏。
//#include <cstdlib>
//
//const uint32_t WIDTH = 800;
//const uint32_t HEIGHT = 600;
//
//class HelloTriangleApplication 
//{
//public:
//    void run() 
//    {
//        initWindow();
//        initVulkan();
//        mainLoop();
//        cleanup();
//    }
//
//private:
//    GLFWwindow* window;
//    VkInstance instance;
//
//    void initWindow() 
//    {
//        // 用于初始化 GLFW 库。
//        glfwInit();
//
//        // GLFW 创建 OpenGL 上下文而设计的，下面调用是控制他不要创建上下文。
//        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//
//        // 创建窗口 宽、高、标题、指定一个监视器打开窗口、OpenGL相关
//        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
//    }
//
//    void initVulkan() 
//    {
//        createInstance();
//    }
//
//    void createInstance()
//    {
//        // 特殊行为的图形引擎
//        VkApplicationInfo appInfo{};
//        // sType 枚举，这里显示的初始值为 nullptr
//        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//        appInfo.pApplicationName = "Hello Triangle";
//        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.pEngineName = "No Engine";
//        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.apiVersion = VK_API_VERSION_1_0;
//
//        // 创建实例提供信息，作用是告诉 Vulkan 驱动程序要使用哪些全局扩展和验证层。
//        VkInstanceCreateInfo createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//        createInfo.pApplicationInfo = &appInfo;
//
//        // 扩展与窗口系统交互，使用GLFW中的内置函数，返回它需要执行的扩展名
//        // 将扩展名传递给结构
//        uint32_t glfwExtensionCount = 0;
//        const char** glfwExtensions;
//
//        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//        
//        createInfo.enabledExtensionCount = glfwExtensionCount;
//        createInfo.ppEnabledExtensionNames = glfwExtensions;
//
//        createInfo.enabledLayerCount = 0;
//
//        /*
//        * 创建实例所需要的一切
//        指向带有创建信息的结构体的指针
//        指向自定义分配器回调的指针
//        指向存储新对象句柄的变量的指针
//        */
//        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
//        
//        if(vkCreateInstance(&createInfo,nullptr,&instance)!=VK_SUCCESS)
//        {
//            throw std::runtime_error("failed to create instance!");
//        }
//    }
//
//    // 运行的持久，可向 mainLoop 添加一个事件循环
//    void mainLoop() 
//    {
//        while (!glfwWindowShouldClose(window)) 
//        {
//            glfwPollEvents();
//        }
//    }
//
//    void cleanup() 
//    {
//        vkDestroyInstance(instance, nullptr);
//        glfwDestroyWindow(window);
//
//        glfwTerminate();
//    }
//};