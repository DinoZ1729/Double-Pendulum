# How to make this code 'do a thing'
## Things you need:
* A compiler and Windows SDK
  * If you already have Visual Studio (any flavor will do), ensure the 'Desktop development with C++' (Microsoft.VisualStudio.Workload.VCTools) workload is installed.
  * If you do not have Visual Studio, you can use the [buildtools installer](https://github.com/DinoZ1729/Double-Pendulum) to keep things lightweight and free. Save the vs_buildtools.exe file somewhere you can easily get to it. Instructions for how to run this are located [here](https://docs.microsoft.com/en-us/visualstudio/install/use-command-line-parameters-to-install-visual-studio?view=vs-2019). Just be sure to install the workload from above.
* a text editor like VS code.
## How to compile:
From a `Developer Command Prompt for VS` (Look in your start menu, or run `<VS Install Path>\Common7\Tools\VsDevCmd.bat`) with your working directory at the base of this repository, call `cl.exe filename.cpp` to produce an executable. Running the result is just as simple, just run the produced `.exe`

Good luck!
