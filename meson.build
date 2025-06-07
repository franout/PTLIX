# Basic library project.
#
# All of the commonly modified parts are above the line. Generally, you
# shouldn't need to modify anything below the line until your project becomes
# fairly complex.


project(
  'ptlix_lib',
  'c',
  version : '1.0.0',
  default_options : ['warning_level=3']
)
project_description = 'Portable Test Library Interface'

compiler = meson.get_compiler('c', native : true)

# See targets for the list of available targets.
# Check for the target architecture
if target_machine.cpu_family() == 'x86_64'
  isa = 'x86_64'
elif target_machine.cpu_family() == 'riscv64'
  isa = 'riscv64'
else
  isa = 'unknown'
endif 

# Check for the target architecture
if target_machine.cpu_family() == 'x86_64'
  arch = 'x86_64'
elif target_machine.cpu_family() == 'riscv64'
  arch = 'riscv64'
elif target_machine.cpu_family() == 'riscv32'
  arch = 'riscv32'
elif target_machine.cpu_family() == 'armv7'
  arch = 'armv7'
elif target_machine.cpu_family() == 'armv8'
  arch = 'armv8'
elif target_machine.cpu_family() == 'aarch64'
  arch = 'aarch64'
elif target_machine.cpu_family() == 'i386'
  arch = 'i386'
elif target_machine.cpu_family() == 'mips'
  arch = 'mips'
else
  arch = 'unknown'
endif 

# Check for the target operating system
if target_machine.system() == 'linux'
  os = 'linux'
elif target_machine.system() == 'windows'
  os = 'windows'
elif target_machine.system() == 'cygwin'
  os = 'cygwin'
elif target_machine.system() == 'darwin'
  os = 'macos'
else
  os = 'unknown'
endif 


project_headers = [
  'include/stl.h',
  'include/stl_types.h',
  'src/cfg/stl_cfg.h',
  'src/error_management/stl_error_management.h',
  'src/scheduler/stl_scheduler.h'
]


include_dirs = [
  'include/',
  'src/cfg/',
  'src/error_management/',
  'src/scheduler/',
  'src/TSSP/',
  'src/tests/' + compiler.get_id().to_upper() + '/' + isa + '/CPU/',
  'src/tests/' + compiler.get_id().to_upper() + '/' + isa + '/utils/',
  'src/tests/' + compiler.get_id().to_upper() + '/' + isa + '/test_setup/',
  'src/tests/' + compiler.get_id().to_upper() + '/' + isa,
]

## TODO make test variable dependent

project_source_files = [
    'src/error_management/stl_error_management.c',
    'src/scheduler/stl_scheduler.c',
    'src/stl.c',
    'src/tests/' + compiler.get_id().to_upper() + '/' + isa + '/CPU/sbst1.c',
    'src/tests/' + compiler.get_id().to_upper() + '/' + isa + '/test_setup/stl_test_setup.c',
    'src/TSSP/CPU/RISCV/stl_al_cpu.c',
    'src/TSSP/CSP/template/stl_al_csp.c',
    'src/TSSP/OS/template/stl_al_os.c',
    'src/TSSP/stl_tssp.c',
    'tests/main_rt.c',
]

project_test_files = [
  # 'tests/src/tests.cpp',
]

build_args = [
  '-D__STL__',
  '-DPTLIX_BUILD',
  '-DSTL_BOOT_TEST',  
  '-DSTL_RUNTIME_TEST',
]



## TODO add the generation of doxygen makefile 
## TODO handle the linker script
## TODO GET THE HEADER FOR THE RELOCATION 
# Add custom defines for the build
#
# ===================================================================

# =======
# Executables
# =======

build_args += [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
]

build_args_lib = '-DSTLLIB_PUBLIC='

project_target = executable(
  meson.project_name(),
  project_source_files,
  include_directories : include_dirs,
  #dependencies: project_dependencies,
  install : true,
  c_args : build_args + build_args_lib ,
)



# ======
# TODO Library 
# ======

#public_headers = include_directories('include')

# Only make public interfaces visible
#if target_machine.system() == 'windows' or target_machine.system() == 'cygwin'
#  build_args += '-DSTLLIB_PUBLIC="__declspec(dllexport)"'
#else
#  build_args += '-DSTLLIB_PUBLIC=__attribute__((visibility("default")))'
#endif
#
#project_target = shared_library(
#  meson.project_name(),
#  project_source_files,
#  install : false,
#  c_args : build_args,
#  gnu_symbol_visibility : 'hidden',
#  #include_directories : public_headers,
#)


# ==========
# Unit Tests
# ==========

#if not meson.is_subproject()
#  add_languages('cpp')
#  subdir('tests')
#
#  test('all_tests',
#    executable(
#      'run_tests',
#      files(project_test_files),
#      dependencies : [project_dep, test_dep],
#      install : false
#    )
#  )
#endif
#