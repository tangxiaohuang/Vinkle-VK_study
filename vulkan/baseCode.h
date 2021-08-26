#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete();
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

static GLFWwindow* window;

static VkInstance instance;
static VkDebugUtilsMessengerEXT debugMessenger;
static VkSurfaceKHR surface;

static VkDevice device;

static VkQueue graphicsQueue;
static VkQueue presentQueue;

static VkSwapchainKHR swapChain;
static std::vector<VkImage> swapChainImages;
static VkFormat swapChainImageFormat;
static VkExtent2D swapChainExtent;
static std::vector<VkImageView> swapChainImageViews;
static std::vector<VkFramebuffer> swapChainFramebuffers;

static VkRenderPass renderPass;
static VkPipeline pipelineLayout;
static VkPipeline graphicsPipeline;

static VkCommandPool commandPool;
static std::vector<VkCommandBuffer> commandBuffers;

static std::vector<VkSemaphore> imageAvailableSemaphores;
static std::vector<VkSemaphore> renderFinishedSemaphores;
static std::vector<VkFence> inFlightFences;
static std::vector<VkFence> imagesInFlight;
static size_t currentFrame = 0;

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

class HelloTriangleApplication {
public:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    

    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    
    void initWindow();

    void initVulkan();

    void mainLoop();

    void cleanup();

    void createInstance();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    void setupDebugMessenger();

    void createSurface();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createSwapChain();

    void createImageViews();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    

    std::vector<const char*> getRequiredExtensions();

    bool checkValidationLayerSupport();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
};
