cmake_minimum_required(VERSION 3.12.1)

include_guard()

macro(add_include_dirs_of_target list target)
  get_target_property(temp_includes ${target} INCLUDE_DIRECTORIES)
  if(NOT "${temp_includes}" STREQUAL temp_includes-NOTFOUND)
    list(APPEND ${list} ${temp_includes})
  endif()
endmacro(add_include_dirs_of_target)

macro(add_source_dirs_and_include_dirs_of_target target source_dirs include_dirs)
  list(APPEND libs ${target})
  set(counter 0)
  set(list_length 1)
  while(${counter} LESS ${list_length})
    list(GET libs ${counter} target_dep)
    if (counter EQUAL 0)
      add_include_dirs_of_target(source_dirs ${target_dep})
    else()
      add_include_dirs_of_target(include_dirs ${target_dep})
    endif()

    get_target_property(linked_libs ${target_dep} LINK_LIBRARIES)
    if (NOT "${linked_libs}" STREQUAL linked_libs-NOTFOUND)
      foreach(linked_lib ${linked_libs})
        if(TARGET ${linked_lib})
          get_target_property(target_type ${linked_lib} TYPE)
          if (NOT target_type STREQUAL "INTERFACE_LIBRARY")
            if(NOT ${linked_lib} IN_LIST libs)
            list(APPEND libs ${linked_lib})
            endif()
          endif ()
        endif ()
      endforeach(linked_lib)
    endif()
    list(LENGTH libs list_length)
    math(EXPR counter "${counter} + 1")
  endwhile()
endmacro()

set(ia_helper_functions_dir ${CMAKE_CURRENT_LIST_DIR} CACHE string "Store helper functions dir" FORCE)

function(target_generate_generics target dir)
  add_source_dirs_and_include_dirs_of_target(${target} source_dirs include_dirs)

  list(TRANSFORM source_dirs PREPEND "-S")
  list(TRANSFORM include_dirs PREPEND "-I")

  add_custom_command(
    TARGET ${target}
    PRE_BUILD
    COMMAND perl GenerateGenericsMain.pl "-N${target}" "-D${CMAKE_CURRENT_SOURCE_DIR}/${dir}" ${source_dirs} ${include_dirs}
    WORKING_DIRECTORY ${ia_helper_functions_dir}/../perl/generate-generics
  )
endfunction(target_generate_generics)

function(target_generate_from_yaml target dir)
  add_source_dirs_and_include_dirs_of_target(${target} source_dirs include_dirs)

  list(TRANSFORM source_dirs PREPEND "-S")
  list(TRANSFORM include_dirs PREPEND "-I")

  add_custom_command(
    TARGET ${target}
    PRE_BUILD
    COMMAND perl GenerateFromYamlMain.pl "-D${CMAKE_CURRENT_SOURCE_DIR}/${dir}" ${source_dirs} ${include_dirs}
    WORKING_DIRECTORY ${ia_helper_functions_dir}/../perl/generate-from-yaml
  )
endfunction(target_generate_from_yaml)
