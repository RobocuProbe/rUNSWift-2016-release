IF (IS_DIRECTORY "$ENV{RUNSWIFT_CHECKOUT_DIR}")
  SET(RUNSWIFT_CHECKOUT_DIR "$ENV{RUNSWIFT_CHECKOUT_DIR}")
ELSE()
  MESSAGE(FATAL_ERROR "Please set the environment variable RUNSWIFT_CHECKOUT_DIR!")
ENDIF()

SET(RUNSWIFT_ROBOT_DIR "${RUNSWIFT_CHECKOUT_DIR}/robot")

INCLUDE_DIRECTORIES(${RUNSWIFT_ROBOT_DIR})
