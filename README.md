# All-Star Game Engine

![ALL STAR GAME ENGINE](https://github.com/Shinkonomi/ARE/blob/main/images/AGELogo.png "All Star Game Engine")

### AGE is simple personal game engine that i'm working on to test different things, so this is just experimental project
#### Currently working on RHI(Rendering Hardware Interface) of the engine using Vulkan API

#### For now the idea is just to simply build a library and the game would just link to the corresponding **.dll** files and use the engine but i might change this later

## Building it

1. First make sure that the latest driver for your graphics card is installed on your operating system
2. Install the latest version of visual studio 2022
3. Open the **AGE.sln** solution file and put the VS debugger on **release** mode (make sure that you're on x64) and then on the **Solution Explorer** window right click on **AGE** and click on **build**
4. After the solution is built navigate to **bin** folder and there should be the .dll files that is needed for building your game