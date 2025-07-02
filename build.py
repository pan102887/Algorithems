from __future__ import annotations
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
import multiprocessing

project_name: str = "Algorithems"
project_root: Path = Path.cwd()


class DependencyElement:
    def __init__(self, name: str,
                 cmd: Optional[str] = None,
                 version_check_arg: str = "--version",
                 required: bool = True,
                 cwd: Optional[Path] = None,
                 install_cmd: Optional[str] = None,
                 candidats: Optional[set[DependencyElement]] = None
                 ):
        self.name = name
        self.cmd = cmd or name
        self.version_check_arg = version_check_arg
        self.required = required
        self.install_cmd = install_cmd
        self.exists: bool = False
        self.version_info: Optional[str] = None
        self.candidats: Optional[set[DependencyElement]] = candidats

    def __print_install_help(self):
        if self.install_cmd is not None:
            printer.info(f"To install {self.name}, run: {self.install_cmd}")
        
    def __print_warn_or_error_info_if_not_exists(self):
        if not self.exists:
            if self.required:
                printer.error(f"❌  {self.cmd} not found")
            else:
                printer.warning(f"⚠️  {self.cmd} not found")
            self.__print_install_help()

    def or_(self, candidate: DependencyElement) -> DependencyElement:
        if self.candidats is None:
            self.candidats = set()
        self.candidats.add(candidate)
        candidate.or_(self)
        
        

    def check(self):
        if shutil.which(self.cmd) is None:
            self.__print_warn_or_error_info_if_not_exists()
            return
                
        try:
            result = subprocess.run(
                [self.cmd, self.version_check_arg],
                cwd=project_root,
                capture_output=True,
                text=True,
                check=False
            )
            if result.returncode == 0:
                lines = (result.stdout or '').splitlines()
                if len(lines) > 0:
                    self.version_info = lines[0].strip()
                    self.exists = True
                    return
                
                lines = (result.stderr or '').splitlines()
                if len(lines) > 0:
                    self.version_info = lines[0].strip()
                    self.exists = True
                    return
            else:
                self.__print_warn_or_error_info_if_not_exists()
        except FileNotFoundError as e:
            self.__print_warn_or_error_info_if_not_exists()

            


class Printer:
    def __init__(self):
        self.header_color = Fore.CYAN
        self.success_color = Fore.GREEN
        self.warning_color = Fore.YELLOW
        self.error_color = Fore.RED

    def header(self, message):
        print(
            f"\n{self.header_color}===================================================={Style.RESET_ALL}")
        print(f"{self.header_color}{message}{Style.RESET_ALL}")
        print(
            f"{self.header_color}===================================================={Style.RESET_ALL}")

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
                cwd=cwd or self.project_root,
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
        code, stdout, stderr = self.run_command(
            [command, version_arg], capture_output=True)
        if code == 0:
            lines: list = stdout.splitlines()
            if len(lines) > 0:
                return lines[0].strip()

            lines: list = stderr.splitlines()
            if len(lines) > 0:
                return lines[0].strip()

        return f"Unkonwn version for {command} (exit code {code})"

    def verify_environment(self, commands: list[Tuple[str, Optional[str]]]) -> dict[str, Optional[str]]:
        self.printer.header("Environment Verification")

        result: dict[str, Optional[str]] = {}
        for command, version_arg in commands:
            if self.check_command_exists(command):
                version_arg = version_arg or "--version"
                version = self.get_command_version(
                    command, version_arg=version_arg)

                result[command] = version
            else:
                result[command] = None
        return result


class BuildTool:
    def __init__(self, printer: Optional[Printer] = None):
        self.printer = printer if printer else Printer()
        self.project_root = Path.cwd()
        self.build_dir = self.project_root / "build"

    def __mv_deps_to_tmp(self, deps_dir: Optional[Path] = None) -> Optional[Path]:
        deps_cache = None
        deps_dir = deps_dir or Path(self.build_dir / "_deps")
        if deps_dir.exists():
            deps_cache = Path("/tmp") / \
                f"{project_name}_deps_cache{os.getpid()}"
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
            self.printer.info(f"Cleaning Directory {self.build_dir}")
            deps_dir = self.build_dir / "_deps"
            cache_dir = self.__mv_deps_to_tmp(deps_dir)
            shutil.rmtree(self.build_dir)
            self.printer.success(
                f"{str(self.build_dir)} cleaned successfully.")

        self.build_dir.mkdir(parents=True, exist_ok=True)
        self.__mv_deps_from_tmp(deps_cache=cache_dir)

    def clean_all(self):
        if self.build_dir.exists():
            shutil.rmtree(self.build_dir)
            printer.success(
                f"Build directory {self.build_dir} cleaned successfully.")

    def prepaire_build_dir(self):
        if not self.build_dir.exists():
            self.build_dir.mkdir(parents=True, exist_ok=True)
            self.printer.success(
                f"Build directory {self.build_dir} created successfully.")

    def prepare_cmake(self, build_type: str = "Release"):
        self.prepaire_build_dir()

        cmake_command = [
            "cmake",
            f"-DCMAKE_BUILD_TYPE={build_type}",
            str(self.project_root)
        ]

        self.printer.info(
            f"Running CMake with command: {' '.join(cmake_command)}")
        result = subprocess.run(
            cmake_command,
            cwd=self.build_dir,
            capture_output=False,
            text=True,
            check=False
        )

        if result.returncode != 0:
            self.printer.error(
                f"CMake failed with exit code {result.returncode}")
            self.printer.error(result.stderr)
            sys.exit(result.returncode)
        else:
            self.printer.success("CMake configuration completed successfully.")
        
    def build(self):
        printer.info(f"Building project {project_name}...")


        cpu_count = multiprocessing.cpu_count()
        result = subprocess.run(
            ["make", f"-j{cpu_count}"],
            cwd=self.build_dir,
            capture_output=False,
            text=True,
            check=False
        )
        if result.returncode != 0:
            printer.error(f"Build failed with exit code {result.returncode}")
            printer.error(result.stderr)
            sys.exit(result.returncode)
        



# ===================================================================================
# ***                                 BUILD SCRIPT                                ***
# ===================================================================================


def depencies_check():
    printer.header(f"DEPENDENCIES CHECK")
    required: list[str] = [
        "gcc",
        "g++",
        "cmake",
    ]
    required: list[DependencyElement] =[
        DependencyElement("gcc"),
        DependencyElement("g++"),
        DependencyElement("cmake"),
    ]
    exit: bool = False
    for dependency in required:
        dependency.check()
        if dependency.exists:
            printer.success(f"✅  {dependency.version_info}")
        exit = not dependency.exists

    if exit:
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description="算法工具包构建和测试脚本")
    parser.add_argument("--clean", "-c", action="store_true", help="清理构建目录")
    parser.add_argument("--clean-all", "-ca",
                        action="store_true", help="完全清理构建目录")
    parser.add_argument("--release", "-r",
                        action="store_true", help="以realse模式构建")
    parser.add_argument(
        "--debug", "-d", action="store_true", help="以debug模式构建")
    parser.add_argument("--test", "-t", action="store_true", help="运行所有测试")
    parser.add_argument("--all", "-a", action="store_true",
                        help="执行完整流程（智能清理、构建、测试、示例")
    parser.add_argument("--c-compiler", choices=["gcc", "clang"])
    parser.add_argument("--cpp-compiler", choices=["g++", "clang++"])
    parser.add_argument("--c-standar", choices=["89", "90", "ANSI", "iSO", "11", "17", "23"])
    parser.add_argument("--make", "-m", action="store_true", help="直接执行make")

    args = parser.parse_args()

    buildTool = BuildTool(printer=printer)

    if args.clean:
        buildTool.clean()
        sys.exit(0)
    elif args.clean_all:
        printer.warning("clean all")
        buildTool.clean_all()
        sys.exit(0)
    elif args.make:
        buildTool.build()
        sys.exit(0)

    buildType: str = "Release"
    if args.release:
        buildType = "Release"
    elif args.debug:
        buildType = "Debug"

    depencies_check()
    buildTool.prepare_cmake(buildType)
    buildTool.build()


colorama_init()
printer = Printer()
if __name__ == "__main__":
    main()
    
