
file(GLOB test_src "*.c*")

foreach(srcfile ${test_src})
  string(REGEX REPLACE "\\.c.?" "" executable ${srcfile})
  get_filename_component(executable ${executable} NAME)
  add_executable(${executable} ${srcfile})
  target_include_directories(${executable} PUBLIC ${CUFINUFFT_INCLUDE_DIRS})
  target_link_libraries(${executable} PUBLIC cufinufft m)
endforeach()

function(add_tests PREC REQ_TOL CHECK_TOL)
  add_test(
    NAME cufinufft1d1_test_GM_${PREC}
    COMMAND cufinufft1d_test 1 1 1e2 2e2 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft1d1_test_SM_${PREC}
    COMMAND cufinufft1d_test 2 1 1e2 2e2 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft1d2_test_GM_${PREC}
    COMMAND cufinufft1d_test 1 2 1e2 2e2 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft2d1_test_GM_${PREC}
    COMMAND cufinufft2d_test 1 1 1e2 2e2 2e4 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft2d1_test_SM_${PREC}
    COMMAND cufinufft2d_test 2 1 1e2 2e2 2e4 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft2d1many_test_GM_${PREC}
    COMMAND cufinufft2dmany_test 1 1 1e2 2e2 5 0 2e4 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft2d1many_test_SM_${PREC}
    COMMAND cufinufft2dmany_test 2 1 1e2 2e2 5 0 2e4 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft2d2many_test_GM_${PREC}
    COMMAND cufinufft2dmany_test 1 2 1e2 2e2 5 0 2e4 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft2d2many_test_SM_${PREC}
    COMMAND cufinufft2dmany_test 2 2 1e2 2e2 5 0 2e4 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  add_test(
    NAME cufinufft3d1_test_GM_${PREC}
    COMMAND cufinufft3d_test 1 1 2 5 10 20 ${REQ_TOL} ${CHECK_TOL} ${PREC})

  if (${PREC} STREQUAL "float")
    add_test(
      NAME cufinufft3d1_test_SM_${PREC}
      COMMAND cufinufft3d_test 2 1 2 5 10 20 ${REQ_TOL} ${CHECK_TOL} ${PREC})

    add_test(
      NAME cufinufft3d1_test_block_${PREC}
      COMMAND cufinufft3d_test 4 1 2 5 10 20 ${REQ_TOL} ${CHECK_TOL} ${PREC})

    add_test(
      NAME cufinufft3d2_test_SM_${PREC}
      COMMAND cufinufft3d_test 2 2 2 5 10 20 ${REQ_TOL} ${CHECK_TOL} ${PREC})
  endif()

  add_test(
    NAME cufinufft3d2_test_GM_${PREC}
    COMMAND cufinufft3d_test 1 2 2 5 10 20 ${REQ_TOL} ${CHECK_TOL} ${PREC})
endfunction()

add_tests(float 1e-5 2e-4)
add_tests(double 1e-12 1e-11)

add_test(NAME cufinufft_public_api COMMAND public_api_test)
