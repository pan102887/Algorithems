from colorama import init as colorama_init
from colorama import Fore
from colorama import Style

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path
from typing import List, Optional, Tuple

project_name: str = "Algorithems"


class Printer:
    def __init__(self):
        self.header_color = Fore.CYAN
        self.success_color = Fore.GREEN
        self.warning_color = Fore.YELLOW
        self.error_color = Fore.RED

    def header(self, message):
        print(f"{self.header_color}===================================================={Style.RESET_ALL}")
        print(f"{self.header_color}{message}{Style.RESET_ALL}")
        print(f"{self.header_color}===================================================={Style.RESET_ALL}")
        
    def info(self, message):
        print(f"{self.header_color}{message}{Style.RESET_ALL}")
        
    def success(self, message):
        print(f"{self.success_color}{message}{Style.RESET_ALL}")
    
        
    def warning(self, message):
        print(f"{self.warning_color}{message}{Style.RESET_ALL}")
        
    def error(self, message):
        print(f"{self.error_color}{message}{Style.RESET_ALL}")
        
        
    
class EnvironmentVerifierTool:
    def __init__(self, printer: Optional[Printer] = None):
        self.printer = printer if printer else Printer()
        self.project_root = Path.cwd()
        
    def run_command(
        self, 
        command: list[str], 
        cwd: Optional[Path] = None,
        capture_output: bool = False
    ) -> Tuple[int, str, str]:
        try:
            result = subprocess.run(
                command,
                cwd = cwd or self.project_root,
                capture_output=capture_output,
                text=True,
                check=False
            )
            return result.returncode, result.stdout or "", result.stderr or ""
        except FileNotFoundError as e:
            return 1, "", f"Command not found: {command[0]}"
        
    
    
    def check_command_exists(self, command: str) -> bool:
        return shutil.which(command) is not None
    
    
    
    def get_command_version(self, command: str, version_arg: str = "--version") -> str:
        code, stdout, stderr = self.run_command([command, version_arg], capture_output=True)
        if code == 0:
            lines:list = stdout.splitlines()
            if len(lines) > 0:
                return lines[0].strip()
            
            lines:list = stderr.splitlines()
            if len(lines) > 0:
                return lines[0].strip()
        
        return f"Unkonwn version for {command} (exit code {code})"
        
        
    def verify_environment(self, commands: list[Tuple[str, Optional[str]]]) -> dict[str, Optional[str]]:
        self.printer.header("Environment Verification")

        result: dict[str, Optional[str]] = {}
        for command, version_arg in commands:
            if self.check_command_exists(command):
                version_arg = version_arg or "--version"
                version = self.get_command_version(command, version_arg=version_arg)
                
                result[command] = version
            else:
                result[command] = None
        return result
           
     
class BuildTool:
    def __init__(self, printer: Optional[Printer] = None):
        self.printer = printer if printer else Printer()
        self.project_root = Path.cwd()
        self.build_dir = self.project_root / "build"
        
        
    def __mv_deps_to_tmp(self, deps_dir:Optional[Path] = None) -> Optional[Path]:
        deps_cache = None
        deps_dir = deps_dir or Path(self.build_dir / "_deps")
        if deps_dir.exists():
            deps_cache = Path("/tmp") / f"{project_name}_deps_cache{os.getpid()}"
            shutil.move(deps_dir, deps_cache)
            return deps_cache
        return None
    
    
    def __defult_deps_dir(self) -> Path:
        return self.build_dir / "_deps"
    
        
    def __mv_deps_from_tmp(self, deps_cache: Optional[Path] = None, deps_dir: Optional[Path] = None):
        if deps_cache is not None and deps_cache.exists():
            deps_dir = deps_dir or self.__defult_deps_dir()
            if not deps_dir.exists():
                deps_dir.mkdir(parents=True, exist_ok=True)
                
            for fileName in os.listdir(deps_cache):
                file_path = deps_cache / fileName
                shutil.move(file_path, deps_dir / fileName)
            # shutil.move(deps_cache, deps_dir)
        
        
    def clean(self):
        cache_dir: Optional[Path] = None
        if self.build_dir.exists():
            self.printer.info(f"Cleaning Build Directory{self.build_dir}")
            deps_dir = self.build_dir / "_deps"
            cache_dir = self.__mv_deps_to_tmp(deps_dir)
            shutil.rmtree(self.build_dir)
            self.printer.success("Build directory cleaned successfully.")
            
        self.build_dir.mkdir(parents=True, exist_ok=True)
        self.__mv_deps_from_tmp(deps_cache=cache_dir)


    def clean_all(self):
        if self.build_dir.exists():
            shutil.rmtree(self.build_dir)
        

        
        
# ===================================================================================
# ***                                 BUILD SCRIPT                                ***
# ===================================================================================


def depencies_check(): 
    required: list[str] = [
        "gcc",
        "g++",
        "cmake",
        
    ]
    
    input_commands: list[Tuple[str, Optional[str]]] = list(map(lambda x: (x, None), required))
    
    tool = EnvironmentVerifierTool()
    result = tool.verify_environment(input_commands)
    
    exit: bool = False
    for dep in required:
        version = result[dep]
        if version is not None:
            printer.success(f"✅ {version}")
        else:
            exit = True
            printer.error(f"❌ {dep} is not installed or not found in PATH")
            
    if exit:
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description="算法工具包构建和测试脚本")
    parser.add_argument("--clean", "-c", action="store_true", help="清理构建目录")
    parser.add_argument("--clean-all", "-ca", action="store_true", help="完全清理构建目录")
    parser.add_argument("--release", "-r", action="store_true", help="以realse模式构建")
    parser.add_argument("--debug", "-d", action="store_true", help="以debug模式构建")
    parser.add_argument("--test", "-t", action="store_true", help="运行所有测试")
    parser.add_argument("--all", "-a", action="store_true", help="执行完整流程（智能清理、构建、测试、示例")
    args = parser.parse_args()
    
    buildTool = BuildTool(printer=printer)
    
    if args.clean:
        buildTool.clean()
        sys.exit(0)
    elif args.clean_all:
        printer.warning("clean all")
        buildTool.clean_all()
        sys.exit(0)
    
    
    


colorama_init()
printer = Printer()
if __name__ == "__main__":
    main()
    
    
    