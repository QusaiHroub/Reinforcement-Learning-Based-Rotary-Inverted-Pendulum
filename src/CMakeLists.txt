set(utils
   ${utils}
   ${CMAKE_CURRENT_SOURCE_DIR}/encoders.cc
   PARENT_SCOPE
)

ADD_SUBDIRECTORY(utils)
ADD_SUBDIRECTORY(pendulum-py-driver)