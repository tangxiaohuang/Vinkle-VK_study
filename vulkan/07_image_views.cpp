//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <stdexcept>
//#include <algorithm>
//#include <vector>
//#include <cstring>
//#include <cstdlib>
//#include <cstdint>
//#include <optional>
//#include <set>
//
//const uint32_t WIDTH = 800;
//const uint32_t HEIGHT = 600;
//
//const std::vector<const char*> validationLayers = {
//    "VK_LAYER_KHRONOS_validation"
//};
//
//// 声明所需设备扩展的列表，类似于要启动的验证层列表
//const std::vector<const char*> deviceExtensions = {
//    VK_KHR_SWAPCHAIN_EXTENSION_NAME
//};
//
//#ifdef NDEBUG
//const bool enableValidationLayers = false;
//#else
//const bool enableValidationLayers = true;
//#endif
//
//VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
//    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//    if (func != nullptr) {
//        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//    }
//    else {
//        return VK_ERROR_EXTENSION_NOT_PRESENT;
//    }
//}
//
//void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
//    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
//    if (func != nullptr) {
//        func(instance, debugMessenger, pAllocator);
//    }
//}
//
//struct QueueFamilyIndices {
//    std::optional<uint32_t> graphicsFamily;
//    std::optional<uint32_t> presentFamily;
//
//    bool isComplete() {
//        return graphicsFamily.has_value() && presentFamily.has_value();
//    }
//};
//
//struct SwapChainSupportDetails {
//    VkSurfaceCapabilitiesKHR capabilities;
//    std::vector<VkSurfaceFormatKHR> formats;
//    std::vector<VkPresentModeKHR> presentModes;
//};
//
//class HelloTriangleApplication {
//public:
//    void run() {
//        initWindow();
//        initVulkan();
//        mainLoop();
//        cleanup();
//    }
//
//private:
//    GLFWwindow* window;
//
//    VkInstance instance;
//    VkDebugUtilsMessengerEXT debugMessenger;
//    VkSurfaceKHR surface;
//
//    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
//    VkDevice device;
//
//    VkQueue graphicsQueue;
//    VkQueue presentQueue;
//
//    VkSwapchainKHR swapChain;
//    std::vector<VkImage> swapChainImages;
//    VkFormat swapChainImageFormat;
//    VkExtent2D swapChainExtent;
//    std::vector<VkImageView> swapChainImageViews;
//
//    void initWindow() {
//        glfwInit();
//
//        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//
//        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
//    }
//
//    void initVulkan() {
//        createInstance();
//        setupDebugMessenger();
//        createSurface();
//        pickPhysicalDevice();
//        createLogicalDevice();
//        createSwapChain();
//    }
//
//    void mainLoop() {
//        while (!glfwWindowShouldClose(window)) {
//            glfwPollEvents();
//        }
//    }
//
//    void cleanup() {
//        vkDestroySwapchainKHR(device, swapChain, nullptr);
//        vkDestroyDevice(device, nullptr);
//
//        if (enableValidationLayers) {
//            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
//        }
//
//        vkDestroySurfaceKHR(instance, surface, nullptr);
//        vkDestroyInstance(instance, nullptr);
//
//        glfwDestroyWindow(window);
//
//        glfwTerminate();
//    }
//
//    void createInstance() {
//        if (enableValidationLayers && !checkValidationLayerSupport()) {
//            throw std::runtime_error("validation layers requested, but not available!");
//        }
//
//        VkApplicationInfo appInfo{};
//        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//        appInfo.pApplicationName = "Hello Triangle";
//        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.pEngineName = "No Engine";
//        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//        appInfo.apiVersion = VK_API_VERSION_1_0;
//
//        VkInstanceCreateInfo createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//        createInfo.pApplicationInfo = &appInfo;
//
//        auto extensions = getRequiredExtensions();
//        // 使用交换链前需要先启用 VK_KHR_swapchain
//        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
//        createInfo.ppEnabledExtensionNames = extensions.data();
//
//        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
//        if (enableValidationLayers) {
//            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//            createInfo.ppEnabledLayerNames = validationLayers.data();
//
//            populateDebugMessengerCreateInfo(debugCreateInfo);
//            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
//        }
//        else {
//            createInfo.enabledLayerCount = 0;
//
//            createInfo.pNext = nullptr;
//        }
//
//        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
//            throw std::runtime_error("failed to create instance!");
//        }
//    }
//
//    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
//        createInfo = {};
//        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
//        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
//        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
//        createInfo.pfnUserCallback = debugCallback;
//    }
//
//    void setupDebugMessenger() {
//        if (!enableValidationLayers) return;
//
//        VkDebugUtilsMessengerCreateInfoEXT createInfo;
//        populateDebugMessengerCreateInfo(createInfo);
//
//        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
//            throw std::runtime_error("failed to set up debug messenger!");
//        }
//    }
//
//    void createSurface() {
//        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
//            throw std::runtime_error("failed to create window surface!");
//        }
//    }
//
//    void pickPhysicalDevice() {
//        uint32_t deviceCount = 0;
//        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
//
//        if (deviceCount == 0) {
//            throw std::runtime_error("failed to find GPUs with Vulkan support!");
//        }
//
//        std::vector<VkPhysicalDevice> devices(deviceCount);
//        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
//
//        for (const auto& device : devices) {
//            if (isDeviceSuitable(device)) {
//                physicalDevice = device;
//                break;
//            }
//        }
//
//        if (physicalDevice == VK_NULL_HANDLE) {
//            throw std::runtime_error("failed to find a suitable GPU!");
//        }
//    }
//
//    void createLogicalDevice() {
//        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
//
//        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
//        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
//
//        float queuePriority = 1.0f;
//        for (uint32_t queueFamily : uniqueQueueFamilies) {
//            VkDeviceQueueCreateInfo queueCreateInfo{};
//            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//            queueCreateInfo.queueFamilyIndex = queueFamily;
//            queueCreateInfo.queueCount = 1;
//            queueCreateInfo.pQueuePriorities = &queuePriority;
//            queueCreateInfos.push_back(queueCreateInfo);
//        }
//
//        VkPhysicalDeviceFeatures deviceFeatures{};
//
//        VkDeviceCreateInfo createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//
//        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
//        createInfo.pQueueCreateInfos = queueCreateInfos.data();
//
//        createInfo.pEnabledFeatures = &deviceFeatures;
//
//        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
//        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
//
//        if (enableValidationLayers) {
//            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//            createInfo.ppEnabledLayerNames = validationLayers.data();
//        }
//        else {
//            createInfo.enabledLayerCount = 0;
//        }
//
//        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
//            throw std::runtime_error("failed to create logical device!");
//        }
//
//        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
//        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
//    }
//
//    // 创建交换链
//    void createSwapChain() {
//        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);
//
//        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
//        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
//        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
//
//        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
//        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
//            imageCount = swapChainSupport.capabilities.maxImageCount;
//        }
//
//        VkSwapchainCreateInfoKHR createInfo{};
//        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
//        createInfo.surface = surface;
//
//        createInfo.minImageCount = imageCount;
//        createInfo.imageFormat = surfaceFormat.format;
//        createInfo.imageColorSpace = surfaceFormat.colorSpace;
//        createInfo.imageExtent = extent;
//        // 指定层的每个图像包含的量，出了开发立体3D应用程序，都是用1
//        createInfo.imageArrayLayers = 1;
//        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
//
//        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
//        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
//
//        if (indices.graphicsFamily != indices.presentFamily) {
//            // 图像可用跨多个队列系列使用，无需明确的所有权转移。
//            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
//            createInfo.queueFamilyIndexCount = 2;
//            createInfo.pQueueFamilyIndices = queueFamilyIndices;
//        }
//        else {
//            //  一个图像一次只能拥有一个 queue family ，并要在另一个 queue family中只用之前必须明确转移所有权。
//            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
//            createInfo.queueFamilyIndexCount = 0;
//            createInfo.pQueueFamilyIndices = nullptr;
//        }
//
//        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
//        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//        createInfo.presentMode = presentMode;
//        createInfo.clipped = VK_TRUE;
//
//        createInfo.oldSwapchain = VK_NULL_HANDLE;
//
//        if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
//            throw std::runtime_error("failed to create swap chain!");
//        }
//
//        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
//        swapChainImages.resize(imageCount);
//        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
//
//        swapChainImageFormat = surfaceFormat.format;
//        swapChainExtent = extent;
//    }
//
//    void createImageViews() {
//        // 调整列表的大小
//        swapChainImageViews.resize(swapChainImages.size());
//
//        // 设置迭代所有交换链图像的循环
//        for (size_t i = 0; i < swapChainImages.size(); i++) {
//            VkImageViewCreateInfo createInfo{};
//            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
//            createInfo.image = swapChainImages[i];
//            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
//            createInfo.format = swapChainImageFormat;
//            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
//            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
//            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
//            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
//            // 该 subresourceRange 字段描述了图像的用途以及应该访问图像的哪个部分
//            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
//            createInfo.subresourceRange.baseMipLevel = 0;
//            createInfo.subresourceRange.layerCount = 1;
//            createInfo.subresourceRange.levelCount = 1;
//            createInfo.subresourceRange.baseArrayLayer = 0;
//
//            // 创建图像视图现在是调用的问题 vkCreateImageView
//            if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
//                throw std::runtime_error("failed to create image views!");
//            }
//        }
//    }
//
//    // 表面格式
//    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
//        for (const auto& availableFormat : availableFormats) {
//            // format 成员指定颜色通道和类型 VK_FORMAT_B8G8R8A8_SRGB 8为无符号整数的顺序存储 BGRA：4*8=32  每个像素总共32未
//            // VK_COLOR_SPACE_SRGB_NONLINEAR_KHR 标志是否支持SRGB颜色空间
//            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
//                return availableFormat;
//            }
//        }
//
//        return availableFormats[0];
//    }
//
//    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
//        for (const auto& availablePresentMode : availablePresentModes) {
//            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
//                return availablePresentMode;
//            }
//        }
//
//        return VK_PRESENT_MODE_FIFO_KHR;
//    }
//
//    // 交换范围->交换链图象的分辨率，相当于要绘制的窗口的分辨率（以像素为单位）
//    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
//        // currentExtent 设置宽度和高度来匹配窗口的分辨路
//        if (capabilities.currentExtent.width != UINT32_MAX) {
//            return capabilities.currentExtent;
//        }
//        else {
//            int width, height;
//            // glfwGetFramebufferSize 以像素为单位查询窗口的分辨率
//            glfwGetFramebufferSize(window, &width, &height);
//
//            VkExtent2D actualExtent = {
//                static_cast<uint32_t>(width),
//                static_cast<uint32_t>(height)
//            };
//
//            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
//            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
//
//            return actualExtent;
//        }
//    }
//
//    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
//        SwapChainSupportDetails details;
//
//        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
//
//        uint32_t formatCount;
//        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
//
//        if (formatCount != 0) {
//            details.formats.resize(formatCount);
//            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
//        }
//
//        uint32_t presentModeCount;
//        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
//
//        if (presentModeCount != 0) {
//            details.presentModes.resize(presentModeCount);
//            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
//        }
//
//        return details;
//    }
//
//    bool isDeviceSuitable(VkPhysicalDevice device) {
//        QueueFamilyIndices indices = findQueueFamilies(device);
//
//        // 附加检查
//        bool extensionsSupported = checkDeviceExtensionSupport(device);
//
//        bool swapChainAdequate = false;
//        if (extensionsSupported) {
//            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
//            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
//        }
//
//        return indices.isComplete() && extensionsSupported && swapChainAdequate;
//    }
//
//    // 修改函数体以枚举扩展并检查是否所有必须的扩展都在其中
//    bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
//        uint32_t extensionCount;
//        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
//
//        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
//        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
//
//        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
//
//        for (const auto& extension : availableExtensions) {
//            requiredExtensions.erase(extension.extensionName);
//        }
//
//        return requiredExtensions.empty();
//    }
//
//    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
//        QueueFamilyIndices indices;
//
//        uint32_t queueFamilyCount = 0;
//        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
//
//        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
//
//        int i = 0;
//        for (const auto& queueFamily : queueFamilies) {
//            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//                indices.graphicsFamily = i;
//            }
//
//            VkBool32 presentSupport = false;
//            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
//
//            if (presentSupport) {
//                indices.presentFamily = i;
//            }
//
//            if (indices.isComplete()) {
//                break;
//            }
//
//            i++;
//        }
//
//        return indices;
//    }
//
//    std::vector<const char*> getRequiredExtensions() {
//        uint32_t glfwExtensionCount = 0;
//        const char** glfwExtensions;
//        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//
//        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
//
//        if (enableValidationLayers) {
//            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//        }
//
//        return extensions;
//    }
//
//    bool checkValidationLayerSupport() {
//        uint32_t layerCount;
//        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//
//        std::vector<VkLayerProperties> availableLayers(layerCount);
//        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
//
//        for (const char* layerName : validationLayers) {
//            bool layerFound = false;
//
//            for (const auto& layerProperties : availableLayers) {
//                if (strcmp(layerName, layerProperties.layerName) == 0) {
//                    layerFound = true;
//                    break;
//                }
//            }
//
//            if (!layerFound) {
//                return false;
//            }
//        }
//
//        return true;
//    }
//
//    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
//        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
//
//        return VK_FALSE;
//    }
//};
//
//int main() {
//    HelloTriangleApplication app;
//
//    try {
//        app.run();
//    }
//    catch (const std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    return EXIT_SUCCESS;
//}