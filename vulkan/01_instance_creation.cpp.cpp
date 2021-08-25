//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//// stdexcept �� iostream ͷ�������ڱ���ʹ�������
//#include <iostream>
//#include <stdexcept>
//// cstdlib ��ͷ�ṩ�� EXIT_SUCCESS �� EXIT_FAILURE �ĺꡣ
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
//        // ���ڳ�ʼ�� GLFW �⡣
//        glfwInit();
//
//        // GLFW ���� OpenGL �����Ķ���Ƶģ���������ǿ�������Ҫ���������ġ�
//        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//
//        // �������� ���ߡ����⡢ָ��һ���������򿪴��ڡ�OpenGL���
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
//        // ������Ϊ��ͼ������
//        VkApplicationInfo appInfo{};
//        // sType ö�٣�������ʾ�ĳ�ʼֵΪ nullptr
//        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//        appInfo.pApplicationName = "Hello Triangle";
//        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.pEngineName = "No Engine";
//        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.apiVersion = VK_API_VERSION_1_0;
//
//        // ����ʵ���ṩ��Ϣ�������Ǹ��� Vulkan ��������Ҫʹ����Щȫ����չ����֤�㡣
//        VkInstanceCreateInfo createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//        createInfo.pApplicationInfo = &appInfo;
//
//        // ��չ�봰��ϵͳ������ʹ��GLFW�е����ú�������������Ҫִ�е���չ��
//        // ����չ�����ݸ��ṹ
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
//        * ����ʵ������Ҫ��һ��
//        ָ����д�����Ϣ�Ľṹ���ָ��
//        ָ���Զ���������ص���ָ��
//        ָ��洢�¶������ı�����ָ��
//        */
//        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
//        
//        if(vkCreateInstance(&createInfo,nullptr,&instance)!=VK_SUCCESS)
//        {
//            throw std::runtime_error("failed to create instance!");
//        }
//    }
//
//    // ���еĳ־ã����� mainLoop ���һ���¼�ѭ��
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