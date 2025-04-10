@echo off
setlocal

REM 设置OpenOCD路径
set OPENOCD_PATH=C:\Program Files (x86)\OpenOCD-20240916-0.12.0\bin

REM 设置OpenOCD配置文件路径
set INTERFACE=C:\Program Files (x86)\OpenOCD-20240916-0.12.0\share\openocd\scripts\interface
set TARGET=C:\Program Files (x86)\OpenOCD-20240916-0.12.0\share\openocd\scripts\target
REM 设置要烧录的ELF文件路径
set ELF_FILE=C:\\Users\\34575\\Desktop\\Cricket_Balance_System\\build\\CBS.elf

REM 检查ELF文件是否存在
if not exist "%ELF_FILE%" (
    echo 错误: 找不到ELF文件 %ELF_FILE%
    exit /b 1
)

REM 运行OpenOCD并烧录ELF文件
"%OPENOCD_PATH%\openocd.exe" -f "%INTERFACE%\cmsis-dap.cfg" -f "%TARGET%\stm32h7x.cfg" -c "program %ELF_FILE% verify reset exit"

if %errorlevel% neq 0 (
    echo failed
    exit /b 1
)

echo success
exit /b 0