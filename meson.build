# Basic library project.
#
# All of the commonly modified parts are above the line. Generally, you
# shouldn't need to modify anything below the line until your project becomes
# fairly complex.


project(
  'ptlix_lib',
  'c',
  version : '1.0.0',
  default_options : ['warning_level=3'],
  meson_version : '>=1.1.0',
  license : 'Apache-2.0',
)
project_description = 'Portable Test Library Interface'

compiler = meson.get_compiler('c', native : true)

# See targets for the list of available targets.
# Check for the target architecture
if target_machine.cpu_family() == 'x86_64'
  isa = 'x86_64'
elif target_machine.cpu_family() == 'riscv64'
  isa = 'riscv64'
elif target_machine.cpu_family() == 'riscv32'
  isa = 'riscv32'
else
  isa = 'unknown'
  meson.error('Unsupported ISA: ' + target_machine.cpu_family())
endif 

# Check for the target architecture
if target_machine.cpu() == 'x86_64'
  arch = 'x86_64'
elif target_machine.cpu() == 'CV32E40P'
  arch = 'cv32e40p'
elif target_machine.cpu() == 'CV32E40X'
  arch = 'cv32e40x'
elif target_machine.cpu() == 'CV32E40S'
  arch = 'cv32e40s'
elif target_machine.cpu() == 'CV32E40X2'
  arch = 'cv32e40x2'
else
  arch = 'unknown'
  meson.error('Unsupported architecture: ' + target_machine.cpu_family())
endif

# Check for the target operating system
if target_machine.system() == 'linux' or target_machine.system() == 'wsl'
  os = 'linux'
elif target_machine.system() == 'windows'
  os = 'windows'
elif target_machine.system() == 'cygwin'
  os = 'cygwin'
elif target_machine.system() == 'darwin'
  os = 'macos'
else
  os = 'unknown'
  meson.error('Unsupported operating system: ' + target_machine.system())
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

## TODO make test-type (cpu,uncore etc) variable dependent
## TODO add meson.build as subproject of sbst

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
]

linker_script = 'linker_scripts/' + compiler.get_id().to_upper() + '/' + arch + '/linker.ld'


build_args = [
  '-D__STL__',
  '-T ' + linker_script,
  '-DPTLIX_BUILD',
]

if get_option('runtime_tests') == true
  build_args += '-DSTL_RUNTIME_TEST'
endif

if get_option('boot_tests') == true
  build_args += '-DSTL_BOOT_TEST'
endif


if get_option('runtime_tests_relocation') == true
  build_args += '-STL_RELOCATED' 
endif 

if get_option('runtime_tests_relocation_table') == true
  build_args += '-DSTL_RELOCATION_TABLE'
endif 

## Get the relocation file 
relocation_header = 'src/tests/' + compiler.get_id().to_upper() + '/' + isa + '/relocation'

include_dirs += relocation_header

# ===================================================================

# ======
# Library 
# ======

# Only make public interfaces visible
if target_machine.system() == 'windows' or target_machine.system() == 'cygwin'
 build_args += '-DSTLLIB_PUBLIC="__declspec(dllexport)"'
else
 build_args += '-DSTLLIB_PUBLIC=__attribute__((visibility("default")))'
endif

if get_option('library_type') == 'shared'
  message('Building shared library')
  project_target = shared_library(
    meson.project_name(),
    project_source_files,
    install : false,
    c_args : build_args,
    include_directories : include_dirs,
    gnu_symbol_visibility : 'hidden',
  )
else
  message('Building static library')
  project_target = static_library(
    meson.project_name(),
    project_source_files,
    install : false,
    c_args : build_args,
  )
endif


# ==========
# TODO Unit Tests
# ==========
if get_option('build_tests')
message('Building unit tests')
if not meson.is_subproject()
  project_test_files = [
    'tests/main_rt.c',
    'tests/main_boot.c',
    #'tests/test_scheduler.c',
    #'tests/test_error_management.c',
    #'tests/test_stl.c',
    #'tests/test_stl_cfg.c',
    #'tests/test_stl_tssp.c',
  ]
 subdir('tests')

test('all_tests',
  executable(
    'run_tests',
    files(project_test_files),
    install : false,
    link_with : project_target
  )
)
endif 

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

endif # get_option('build_tests')


# ==========
# Doxygen-based Documentation
# ==========
if get_option('build_docs')==true 
  message('Building documentation')
  doxygen = find_program('doxygen', required : false)
  if doxygen.found()
    run_target('docs', command : [doxygen, meson.project_source_root() + '/Doxyfile'])
    message('Documentation generated successfully in ' + meson.current_build_dir() + '/docs/.')
  else
    warning('Doxygen not found, documentation will not be generated.')
  endif
endif # get_option('build_docs') 
