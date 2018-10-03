
# THIS FILE HAS BEEN AUTOMATICALLY GENERATED. DO NOT EDIT IT DIRECTLY!

cmake_minimum_required(VERSION 3.12.1)
include_guard()

if(NOT DEFINED IA_PLATFORM)
	message(FATAL_ERROR "IA_PLATFORM is not set. It must be one of \"android\", \"ios\" or \"windows\".")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -UNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -UNDEBUG")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

add_definitions(-DHAVE_MEMMOVE)
find_package(HelperFunctions)


# --------------  Modules for group "common"  --------------n

unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/common/clib/c/shared modules/common/clib/c/shared/container modules/common/clib/c/shared/memory-management modules/common/clib/c/shared/memory-management/allocation-tracking modules/common/clib/c/shared/supporting-classes modules/common/clib/c/shared/supporting-classes/concurrency)
list(APPEND iaclib_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/common/clib/c/shared/IAAssert.h modules/common/clib/c/shared/IALibrary+SendOnMemoryWarningNotification.h modules/common/clib/c/shared/IALibrary.h modules/common/clib/c/shared/IAObject.h modules/common/clib/c/shared/container/IAArray.h modules/common/clib/c/shared/container/IAArrayIterator.h modules/common/clib/c/shared/container/IAArrayList.h modules/common/clib/c/shared/container/IAArrayListIterator.h modules/common/clib/c/shared/container/IAAutoExpandingHashMap.h modules/common/clib/c/shared/container/IAAutoExpandingHashMapIterator.h modules/common/clib/c/shared/container/IAHashMap.h modules/common/clib/c/shared/container/IAHashMapIterator.h modules/common/clib/c/shared/container/IAStructArrayList.h modules/common/clib/c/shared/memory-management/IAAutoreleasePool+Internal.h modules/common/clib/c/shared/memory-management/IAAutoreleasePool.h modules/common/clib/c/shared/memory-management/IAMemoryPool.h modules/common/clib/c/shared/memory-management/IAMemoryPoolElement.h modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTracker.h modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTrackerElement.h modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTracking+Internal.h modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTracking.h modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTrackingDelegate.h modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTrackingElement.h modules/common/clib/c/shared/supporting-classes/IACharArray+Internal.h modules/common/clib/c/shared/supporting-classes/IACharArray.h modules/common/clib/c/shared/supporting-classes/IAHashing.h modules/common/clib/c/shared/supporting-classes/IANotificationDelegate.h modules/common/clib/c/shared/supporting-classes/IAOperatingSystem.h modules/common/clib/c/shared/supporting-classes/IAString.h modules/common/clib/c/shared/supporting-classes/IATime.h modules/common/clib/c/shared/supporting-classes/concurrency/IACondition.h modules/common/clib/c/shared/supporting-classes/concurrency/IALock.h modules/common/clib/c/shared/supporting-classes/concurrency/IAPosixAvailable.h modules/common/clib/c/shared/supporting-classes/concurrency/IARecursiveLock.h)
list(APPEND ia_source_c_files modules/common/clib/c/shared/IALibrary.c modules/common/clib/c/shared/container/IAArray.c modules/common/clib/c/shared/container/IAArrayIterator.c modules/common/clib/c/shared/container/IAArrayList.c modules/common/clib/c/shared/container/IAArrayListIterator.c modules/common/clib/c/shared/container/IAAutoExpandingHashMap.c modules/common/clib/c/shared/container/IAAutoExpandingHashMapIterator.c modules/common/clib/c/shared/container/IAHashMap.c modules/common/clib/c/shared/container/IAHashMapIterator.c modules/common/clib/c/shared/memory-management/IAAutoreleasePool.c modules/common/clib/c/shared/memory-management/IAMemoryPool.c modules/common/clib/c/shared/memory-management/IAMemoryPoolElement.c modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTracker.c modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTrackerElement.c modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTracking.c modules/common/clib/c/shared/memory-management/allocation-tracking/IAAllocationTrackingElement.c modules/common/clib/c/shared/supporting-classes/IACharArray.c modules/common/clib/c/shared/supporting-classes/IAHashing.c modules/common/clib/c/shared/supporting-classes/IAString.c modules/common/clib/c/shared/supporting-classes/concurrency/IACondition.c modules/common/clib/c/shared/supporting-classes/concurrency/IALock.c modules/common/clib/c/shared/supporting-classes/concurrency/IARecursiveLock.c)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/clib/c/android modules/common/clib/c/android/generated-jni-headers modules/common/clib/c/android/helper-classes)
	list(APPEND ia_source_h_files modules/common/clib/c/android/IAJni.h modules/common/clib/c/android/IALogger.h modules/common/clib/c/android/IAOperatingSystem+Native.h modules/common/clib/c/android/generated-jni-headers/com_impsapps_impsengine_common_clib_Library.h modules/common/clib/c/android/helper-classes/IANativeObject.h modules/common/clib/c/android/helper-classes/JNIEnv+HelperMethods.h)
	list(APPEND ia_source_c_files modules/common/clib/c/android/IAJni.c modules/common/clib/c/android/IALibrary.c modules/common/clib/c/android/IATime.c modules/common/clib/c/android/helper-classes/IANativeObject.c modules/common/clib/c/android/helper-classes/JNIEnv.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/common/clib/c/ios)
	list(APPEND ia_source_h_files modules/common/clib/c/ios/IALogger.h modules/common/clib/c/ios/IAOperatingSystem+Native.h)
	list(APPEND ia_source_c_files modules/common/clib/c/ios/IATime.m)
endif()
if(${IA_PLATFORM} STREQUAL windows)
	list(APPEND ia_include_dirs modules/common/clib/c/windows)
	list(APPEND ia_source_h_files modules/common/clib/c/windows/IACLibWinMappings.h modules/common/clib/c/windows/IALogger.h modules/common/clib/c/windows/IAOperatingSystem+Native.h)
	list(APPEND ia_source_c_files modules/common/clib/c/windows/IACLibWinMappings.c)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/clib/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaclib STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaclib PUBLIC ${ia_include_dirs})
	if(${IA_PLATFORM} STREQUAL android)
		target_link_libraries(iaclib android log)
	endif()
	target_generate_generics(iaclib include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/common/mathlib/c/shared)
list(APPEND iamathlib_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/common/mathlib/c/shared/IAMath.h)
list(APPEND ia_source_c_files modules/common/mathlib/c/shared/IAMath.c)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/mathlib/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iamathlib STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iamathlib PUBLIC ${ia_include_dirs})
	target_generate_generics(iamathlib include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/androidlib/c/android)
	list(APPEND ia_source_h_files modules/common/androidlib/c/android/IAAndroidLib+Jni.h)
	list(APPEND ia_source_c_files modules/common/androidlib/c/android/IAAndroidLib.c)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/androidlib/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaandroidlib STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaandroidlib PUBLIC ${ia_include_dirs})
	target_link_libraries(iaandroidlib iaclib)
	target_generate_generics(iaandroidlib include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/concurrentlib/c/android modules/common/concurrentlib/c/android+ios)
	list(APPEND ia_source_h_files modules/common/concurrentlib/c/android+ios/IAAsyncTask.h modules/common/concurrentlib/c/android+ios/IAParallelThread.h modules/common/concurrentlib/c/android+ios/IAProcess+AndroidNative.h modules/common/concurrentlib/c/android+ios/IAThreadPool.h modules/common/concurrentlib/c/android+ios/IAThreadPoolInstance.h modules/common/concurrentlib/c/android+ios/IAThreadPoolWaitingQueueItem.h)
	list(APPEND ia_source_c_files modules/common/concurrentlib/c/android+ios/IAAsyncTask.c modules/common/concurrentlib/c/android+ios/IAParallelThread.c modules/common/concurrentlib/c/android+ios/IAThreadPool.c modules/common/concurrentlib/c/android+ios/IAThreadPoolWaitingQueueItem.c modules/common/concurrentlib/c/android/IAProcess.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/common/concurrentlib/c/android+ios)
	list(APPEND ia_source_h_files modules/common/concurrentlib/c/android+ios/IAAsyncTask.h modules/common/concurrentlib/c/android+ios/IAParallelThread.h modules/common/concurrentlib/c/android+ios/IAProcess+AndroidNative.h modules/common/concurrentlib/c/android+ios/IAThreadPool.h modules/common/concurrentlib/c/android+ios/IAThreadPoolInstance.h modules/common/concurrentlib/c/android+ios/IAThreadPoolWaitingQueueItem.h)
	list(APPEND ia_source_c_files modules/common/concurrentlib/c/android+ios/IAAsyncTask.c modules/common/concurrentlib/c/android+ios/IAParallelThread.c modules/common/concurrentlib/c/android+ios/IAThreadPool.c modules/common/concurrentlib/c/android+ios/IAThreadPoolWaitingQueueItem.c)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/concurrentlib/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaconcurrentlib STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaconcurrentlib PUBLIC ${ia_include_dirs})
	target_link_libraries(iaconcurrentlib iaclib)
	target_generate_generics(iaconcurrentlib include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/expat/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs dependencies/expat-2.2.1/lib)
list(APPEND ia_source_c_files dependencies/expat-2.2.1/lib/xmlparse.c dependencies/expat-2.2.1/lib/xmlrole.c dependencies/expat-2.2.1/lib/xmltok_ns.c dependencies/expat-2.2.1/lib/xmltok.c)
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaexpat STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaexpat PUBLIC ${ia_include_dirs})
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/common/input-output/c/shared modules/common/input-output/c/shared/key-value-countainer modules/common/input-output/c/shared/localisation modules/common/input-output/c/shared/main)
list(APPEND iainput_output_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/common/input-output/c/shared/key-value-countainer/IAKeyValueElement.h modules/common/input-output/c/shared/key-value-countainer/IAKeyValueElementAttributes.h modules/common/input-output/c/shared/key-value-countainer/IAKeyValueElementOperations.h modules/common/input-output/c/shared/key-value-countainer/IAKeyValueHashMap.h modules/common/input-output/c/shared/localisation/IALocalisation.h modules/common/input-output/c/shared/main/IAAtlasAssets.h modules/common/input-output/c/shared/main/IAAtlasAssetsAttributes.h modules/common/input-output/c/shared/main/IAStorage+Native.h modules/common/input-output/c/shared/main/IAStorage.h modules/common/input-output/c/shared/main/IAString+Assets+Native.h modules/common/input-output/c/shared/main/IAString+Assets.h modules/common/input-output/c/shared/main/IA_XML_Atlas.h modules/common/input-output/c/shared/main/IA_XML_Strings.h)
list(APPEND ia_source_c_files modules/common/input-output/c/shared/key-value-countainer/IAKeyValueElement.c modules/common/input-output/c/shared/key-value-countainer/IAKeyValueElementAttributes.c modules/common/input-output/c/shared/key-value-countainer/IAKeyValueElementOperations.c modules/common/input-output/c/shared/key-value-countainer/IAKeyValueHashMap.c modules/common/input-output/c/shared/main/IAAtlasAssets.c modules/common/input-output/c/shared/main/IAStorage.c modules/common/input-output/c/shared/main/IAString+Assets.c modules/common/input-output/c/shared/main/IA_XML_Atlas.c modules/common/input-output/c/shared/main/IA_XML_Strings.c)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/input-output/c/android)
	list(APPEND ia_source_c_files modules/common/input-output/c/android/IALocalisation.c modules/common/input-output/c/android/IAStorage.c modules/common/input-output/c/android/IAString+Assets.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/common/input-output/c/ios)
	list(APPEND ia_source_c_files modules/common/input-output/c/ios/IALocalisation.m modules/common/input-output/c/ios/IAStorage.m modules/common/input-output/c/ios/IAString.m)
endif()
if(${IA_PLATFORM} STREQUAL windows)
	list(APPEND ia_include_dirs modules/common/input-output/c/windows)
	list(APPEND ia_source_h_files modules/common/input-output/c/windows/IAInputOutputWinMappings.h)
	list(APPEND ia_source_c_files modules/common/input-output/c/windows/IAInputOutputWinMappings.c)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/input-output/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iainput_output STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iainput_output PUBLIC ${ia_include_dirs})
	target_link_libraries(iainput_output iaclib iaexpat)
	target_generate_generics(iainput_output include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/common/opengl/c/shared modules/common/opengl/c/shared/framebuffers modules/common/opengl/c/shared/graphics modules/common/opengl/c/shared/graphics/animation modules/common/opengl/c/shared/graphics/buffer modules/common/opengl/c/shared/graphics/text modules/common/opengl/c/shared/graphics/texture modules/common/opengl/c/shared/helperstructs modules/common/opengl/c/shared/layout modules/common/opengl/c/shared/main modules/common/opengl/c/shared/matrix modules/common/opengl/c/shared/shaders modules/common/opengl/c/shared/shaders/IAColorRectProgram modules/common/opengl/c/shared/shaders/IAImageProgram modules/common/opengl/c/shared/supporting-classes)
list(APPEND iaopengl_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/common/opengl/c/shared/IAOpenGL.h modules/common/opengl/c/shared/framebuffers/IACurrentFramebuffer.h modules/common/opengl/c/shared/framebuffers/IADefaultFramebuffer+Internal.h modules/common/opengl/c/shared/framebuffers/IADefaultFramebuffer.h modules/common/opengl/c/shared/framebuffers/IAOffscreenFramebuffer.h modules/common/opengl/c/shared/graphics/IABackgroundColor.h modules/common/opengl/c/shared/graphics/IAColorRect.h modules/common/opengl/c/shared/graphics/IADrawable.h modules/common/opengl/c/shared/graphics/IADrawableRect.h modules/common/opengl/c/shared/graphics/IAGraphicRect.h modules/common/opengl/c/shared/graphics/IAImage.h modules/common/opengl/c/shared/graphics/IAImageAttributes.h modules/common/opengl/c/shared/graphics/IAImageContext.h modules/common/opengl/c/shared/graphics/IATrimmedRect.h modules/common/opengl/c/shared/graphics/animation/IAAcceleration.h modules/common/opengl/c/shared/graphics/animation/IAAccelerationAnimation.h modules/common/opengl/c/shared/graphics/animation/IAAccelerationAnimationAttributes.h modules/common/opengl/c/shared/graphics/animation/IACompositedAnimation.h modules/common/opengl/c/shared/graphics/animation/IACompositedAnimationDelegate.h modules/common/opengl/c/shared/graphics/animation/IACompositedAnimationDelegateAttributes.h modules/common/opengl/c/shared/graphics/animation/IAFrameAnimation.h modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationAttributes.h modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationCalculation.h modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationGroup.h modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationGroupAttributes.h modules/common/opengl/c/shared/graphics/animation/IAPauseAnimation.h modules/common/opengl/c/shared/graphics/buffer/IAArrayBuffer.h modules/common/opengl/c/shared/graphics/buffer/IABuffer.h modules/common/opengl/c/shared/graphics/buffer/IAElementArrayBuffer.h modules/common/opengl/c/shared/graphics/text/IAColorableFontAtlas.h modules/common/opengl/c/shared/graphics/text/IAFontAtlas+IterateOverGlyphList.h modules/common/opengl/c/shared/graphics/text/IAFontAtlas.h modules/common/opengl/c/shared/graphics/text/IAFontInformation.h modules/common/opengl/c/shared/graphics/text/IAFontInformationAttributes.h modules/common/opengl/c/shared/graphics/text/IAGlyph.h modules/common/opengl/c/shared/graphics/text/IAGlyphInformation.h modules/common/opengl/c/shared/graphics/text/IAKerningAmount.h modules/common/opengl/c/shared/graphics/text/IATextAlignment.h modules/common/opengl/c/shared/graphics/text/IAUTF8Helper.h modules/common/opengl/c/shared/graphics/texture/IABitmap+Native.h modules/common/opengl/c/shared/graphics/texture/IABitmap.h modules/common/opengl/c/shared/graphics/texture/IABitmapManager.h modules/common/opengl/c/shared/graphics/texture/IABitmapManagerSingleton.h modules/common/opengl/c/shared/graphics/texture/IATexture.h modules/common/opengl/c/shared/graphics/texture/IATextureDelegate.h modules/common/opengl/c/shared/graphics/texture/IATextureDelegateAttributes.h modules/common/opengl/c/shared/graphics/texture/IATextureSelection.h modules/common/opengl/c/shared/graphics/texture/IATextureSelectionData.h modules/common/opengl/c/shared/helperstructs/IAColor.h modules/common/opengl/c/shared/helperstructs/IAPoint.h modules/common/opengl/c/shared/helperstructs/IAPos.h modules/common/opengl/c/shared/helperstructs/IARect.h modules/common/opengl/c/shared/helperstructs/IASize.h modules/common/opengl/c/shared/layout/IAIntent.h modules/common/opengl/c/shared/layout/IAView.h modules/common/opengl/c/shared/layout/IAViewAttributes.h modules/common/opengl/c/shared/layout/IAViewHolder.h modules/common/opengl/c/shared/main/IACurrentFrame+Private.h modules/common/opengl/c/shared/main/IACurrentFrame.h modules/common/opengl/c/shared/main/IAOpenGLConstants.h modules/common/opengl/c/shared/main/IAOpenGLResourceDelegate.h modules/common/opengl/c/shared/main/IAOpenGLResourceDelegateAttributes.h modules/common/opengl/c/shared/main/IAOpenGLResourceManager.h modules/common/opengl/c/shared/matrix/IAMatrix44.h modules/common/opengl/c/shared/shaders/IAColorRectProgram/IAColorRectProgram.h modules/common/opengl/c/shared/shaders/IAColorRectProgram/IAColorRectProgramSingleton.h modules/common/opengl/c/shared/shaders/IAImageProgram/IAImageProgram.h modules/common/opengl/c/shared/shaders/IAImageProgram/IAImageProgramSingleton.h modules/common/opengl/c/shared/shaders/IAProgram.h modules/common/opengl/c/shared/shaders/IAShader.h modules/common/opengl/c/shared/supporting-classes/IADrawingBounds.h modules/common/opengl/c/shared/supporting-classes/IAMeassure.h modules/common/opengl/c/shared/supporting-classes/IAOpenGLAssert.h modules/common/opengl/c/shared/supporting-classes/IAStopwatch.h modules/common/opengl/c/shared/supporting-classes/IAViewPort+Internal.h modules/common/opengl/c/shared/supporting-classes/IAViewPort.h)
list(APPEND ia_source_c_files modules/common/opengl/c/shared/IAOpenGL.c modules/common/opengl/c/shared/framebuffers/IACurrentFramebuffer.c modules/common/opengl/c/shared/framebuffers/IADefaultFramebuffer.c modules/common/opengl/c/shared/framebuffers/IAOffscreenFramebuffer.c modules/common/opengl/c/shared/graphics/IABackgroundColor.c modules/common/opengl/c/shared/graphics/IAColorRect.c modules/common/opengl/c/shared/graphics/IADrawable.c modules/common/opengl/c/shared/graphics/IADrawableRect.c modules/common/opengl/c/shared/graphics/IAGraphicRect.c modules/common/opengl/c/shared/graphics/IAImage.c modules/common/opengl/c/shared/graphics/IAImageAttributes.c modules/common/opengl/c/shared/graphics/IAImageContext.c modules/common/opengl/c/shared/graphics/IATrimmedRect.c modules/common/opengl/c/shared/graphics/animation/IAAcceleration.c modules/common/opengl/c/shared/graphics/animation/IAAccelerationAnimation.c modules/common/opengl/c/shared/graphics/animation/IAAccelerationAnimationAttributes.c modules/common/opengl/c/shared/graphics/animation/IACompositedAnimation.c modules/common/opengl/c/shared/graphics/animation/IACompositedAnimationDelegate.c modules/common/opengl/c/shared/graphics/animation/IACompositedAnimationDelegateAttributes.c modules/common/opengl/c/shared/graphics/animation/IAFrameAnimation.c modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationAttributes.c modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationCalculation.c modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationGroup.c modules/common/opengl/c/shared/graphics/animation/IAFrameAnimationGroupAttributes.c modules/common/opengl/c/shared/graphics/animation/IAPauseAnimation.c modules/common/opengl/c/shared/graphics/buffer/IAArrayBuffer.c modules/common/opengl/c/shared/graphics/buffer/IABuffer.c modules/common/opengl/c/shared/graphics/buffer/IAElementArrayBuffer.c modules/common/opengl/c/shared/graphics/text/IAColorableFontAtlas.c modules/common/opengl/c/shared/graphics/text/IAFontAtlas.c modules/common/opengl/c/shared/graphics/text/IAFontInformation.c modules/common/opengl/c/shared/graphics/text/IAFontInformationAttributes.c modules/common/opengl/c/shared/graphics/text/IAGlyph.c modules/common/opengl/c/shared/graphics/text/IAKerningAmount.c modules/common/opengl/c/shared/graphics/text/IAUTF8Helper.c modules/common/opengl/c/shared/graphics/texture/IABitmap.c modules/common/opengl/c/shared/graphics/texture/IABitmapManager.c modules/common/opengl/c/shared/graphics/texture/IABitmapManagerSingleton.c modules/common/opengl/c/shared/graphics/texture/IATexture.c modules/common/opengl/c/shared/graphics/texture/IATextureDelegate.c modules/common/opengl/c/shared/graphics/texture/IATextureDelegateAttributes.c modules/common/opengl/c/shared/graphics/texture/IATextureSelection.c modules/common/opengl/c/shared/graphics/texture/IATextureSelectionData.c modules/common/opengl/c/shared/helperstructs/IAColor.c modules/common/opengl/c/shared/helperstructs/IAPoint.c modules/common/opengl/c/shared/helperstructs/IAPos.c modules/common/opengl/c/shared/helperstructs/IARect.c modules/common/opengl/c/shared/helperstructs/IASize.c modules/common/opengl/c/shared/layout/IAIntent.c modules/common/opengl/c/shared/layout/IAView.c modules/common/opengl/c/shared/layout/IAViewAttributes.c modules/common/opengl/c/shared/layout/IAViewHolder.c modules/common/opengl/c/shared/main/IACurrentFrame.c modules/common/opengl/c/shared/main/IAOpenGLConstants.c modules/common/opengl/c/shared/main/IAOpenGLResourceDelegate.c modules/common/opengl/c/shared/main/IAOpenGLResourceDelegateAttributes.c modules/common/opengl/c/shared/main/IAOpenGLResourceManager.c modules/common/opengl/c/shared/matrix/IAMatrix44.c modules/common/opengl/c/shared/shaders/IAColorRectProgram/IAColorRectProgram.c modules/common/opengl/c/shared/shaders/IAColorRectProgram/IAColorRectProgramSingleton.c modules/common/opengl/c/shared/shaders/IAImageProgram/IAImageProgram.c modules/common/opengl/c/shared/shaders/IAImageProgram/IAImageProgramSingleton.c modules/common/opengl/c/shared/shaders/IAProgram.c modules/common/opengl/c/shared/shaders/IAShader.c modules/common/opengl/c/shared/supporting-classes/IADrawingBounds.c modules/common/opengl/c/shared/supporting-classes/IAMeassure.c modules/common/opengl/c/shared/supporting-classes/IAStopwatch.c modules/common/opengl/c/shared/supporting-classes/IAViewPort.c)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/opengl/c/android)
	list(APPEND ia_source_h_files modules/common/opengl/c/android/IABitmap+Jni.h modules/common/opengl/c/android/IAOpenGLHeaders.h)
	list(APPEND ia_source_c_files modules/common/opengl/c/android/IABitmap.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/common/opengl/c/ios)
	list(APPEND ia_source_h_files modules/common/opengl/c/ios/IAOpenGLHeaders.h)
	list(APPEND ia_source_c_files modules/common/opengl/c/ios/IABitmap.m)
endif()
if(${IA_PLATFORM} STREQUAL windows)
	list(APPEND ia_include_dirs modules/common/opengl/c/windows)
	list(APPEND ia_source_h_files modules/common/opengl/c/windows/IAOpenGLHeaders.h modules/common/opengl/c/windows/IAOpenGLWinMappings.h)
	list(APPEND ia_source_c_files modules/common/opengl/c/windows/IAOpenGLWinMappings.c)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/opengl/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaopengl STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaopengl PUBLIC ${ia_include_dirs})
	target_link_libraries(iaopengl iaclib iaexpat iainput_output iamathlib)
	if(${IA_PLATFORM} STREQUAL android)
		target_link_libraries(iaopengl GLESv2 EGL)
	endif()
	if(${IA_PLATFORM} STREQUAL windows)
		target_link_libraries(iaopengl glew)
	endif()
	target_generate_generics(iaopengl include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/common/multi-touch/c/shared)
list(APPEND iamulti_touch_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/common/multi-touch/c/shared/IAButton.h modules/common/multi-touch/c/shared/IAButtonAttributes.h modules/common/multi-touch/c/shared/IAMultiTouch.h modules/common/multi-touch/c/shared/IAOverscrollingBehavior.h modules/common/multi-touch/c/shared/IAOverscrollingHandler.h modules/common/multi-touch/c/shared/IAScrollView.h modules/common/multi-touch/c/shared/IAScrollViewAttributes.h modules/common/multi-touch/c/shared/IAScrollingData.h modules/common/multi-touch/c/shared/IATouch.h modules/common/multi-touch/c/shared/IATouchDelegate.h modules/common/multi-touch/c/shared/IATouchDelegateAttributes.h modules/common/multi-touch/c/shared/IATouchHandler.h modules/common/multi-touch/c/shared/IATouchManager.h)
list(APPEND ia_source_c_files modules/common/multi-touch/c/shared/IAButton.c modules/common/multi-touch/c/shared/IAButtonAttributes.c modules/common/multi-touch/c/shared/IAMultiTouch.c modules/common/multi-touch/c/shared/IAOverscrollingHandler.c modules/common/multi-touch/c/shared/IAScrollView.c modules/common/multi-touch/c/shared/IAScrollViewAttributes.c modules/common/multi-touch/c/shared/IAScrollingData.c modules/common/multi-touch/c/shared/IATouch.c modules/common/multi-touch/c/shared/IATouchDelegate.c modules/common/multi-touch/c/shared/IATouchDelegateAttributes.c modules/common/multi-touch/c/shared/IATouchHandler.c modules/common/multi-touch/c/shared/IATouchManager.c)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/multi-touch/c/android modules/common/multi-touch/c/android/generated-jni-headers)
	list(APPEND ia_source_h_files modules/common/multi-touch/c/android/IATouchManagerHandler+Jni.h modules/common/multi-touch/c/android/generated-jni-headers/com_impsapps_impsengine_common_multitouch_TouchListener.h)
	list(APPEND ia_source_c_files modules/common/multi-touch/c/android/IATouchManagerHandler.c)
endif()
if(${IA_PLATFORM} STREQUAL windows)
	list(APPEND ia_include_dirs modules/common/multi-touch/c/windows)
	list(APPEND ia_source_h_files modules/common/multi-touch/c/windows/IAWinTouchHandler.h)
	list(APPEND ia_source_c_files modules/common/multi-touch/c/windows/IAWinTouchHandler.c)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/multi-touch/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iamulti_touch STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iamulti_touch PUBLIC ${ia_include_dirs})
	target_link_libraries(iamulti_touch iaopengl iaclib)
	target_generate_generics(iamulti_touch include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/common/opengl-renderer/c/shared modules/common/opengl-renderer/c/shared/main modules/common/opengl-renderer/c/shared/main/opengl-surface-options)
list(APPEND iaopengl_renderer_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/common/opengl-renderer/c/shared/IAAppEntryPoint+Core.h modules/common/opengl-renderer/c/shared/IAAppEntryPoint.h modules/common/opengl-renderer/c/shared/main/IAApp.h modules/common/opengl-renderer/c/shared/main/IAAppAttributes.h modules/common/opengl-renderer/c/shared/main/IAAppHandler+Native.h modules/common/opengl-renderer/c/shared/main/IAAppHandler.h modules/common/opengl-renderer/c/shared/main/opengl-surface-options/IAColorFormat.h modules/common/opengl-renderer/c/shared/main/opengl-surface-options/IADepthFormat.h modules/common/opengl-renderer/c/shared/main/opengl-surface-options/IAInterfaceOrientationMask.h modules/common/opengl-renderer/c/shared/main/opengl-surface-options/IAMultisample.h modules/common/opengl-renderer/c/shared/main/opengl-surface-options/IAStencilFormat.h)
list(APPEND ia_source_c_files modules/common/opengl-renderer/c/shared/IAAppEntryPoint.c modules/common/opengl-renderer/c/shared/main/IAApp.c modules/common/opengl-renderer/c/shared/main/IAAppAttributes.c modules/common/opengl-renderer/c/shared/main/IAAppHandler.c)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/common/opengl-renderer/c/android modules/common/opengl-renderer/c/android/generated-jni-headers)
	list(APPEND ia_source_h_files modules/common/opengl-renderer/c/android/generated-jni-headers/com_impsapps_impsengine_common_openglrenderer_BaseActivity.h modules/common/opengl-renderer/c/android/generated-jni-headers/com_impsapps_impsengine_common_openglrenderer_IASurfaceRenderer.h)
	list(APPEND ia_source_c_files modules/common/opengl-renderer/c/android/IAJniWrapper.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/common/opengl-renderer/c/ios modules/common/opengl-renderer/c/ios/opengl-surface-options)
	list(APPEND ia_source_h_files modules/common/opengl-renderer/c/ios/IADefaultUIApplicationDelegate.h modules/common/opengl-renderer/c/ios/IAOpenGLViewController.h modules/common/opengl-renderer/c/ios/IAOpenGLViewControllerHolder.h modules/common/opengl-renderer/c/ios/opengl-surface-options/IAColorFormat+iOS.h modules/common/opengl-renderer/c/ios/opengl-surface-options/IADepthFormat+iOS.h modules/common/opengl-renderer/c/ios/opengl-surface-options/IAInterfaceOrientationMask+iOS.h modules/common/opengl-renderer/c/ios/opengl-surface-options/IAMultisample+iOS.h modules/common/opengl-renderer/c/ios/opengl-surface-options/IAStencilFormat+iOS.h)
	list(APPEND ia_source_c_files modules/common/opengl-renderer/c/ios/IADefaultUIApplicationDelegate.m modules/common/opengl-renderer/c/ios/IAOpenGLViewController.m modules/common/opengl-renderer/c/ios/IAOpenGLViewControllerHolder.m modules/common/opengl-renderer/c/ios/opengl-surface-options/IAColorFormat+iOS.m modules/common/opengl-renderer/c/ios/opengl-surface-options/IADepthFormat+iOS.m modules/common/opengl-renderer/c/ios/opengl-surface-options/IAInterfaceOrientationMask+iOS.m modules/common/opengl-renderer/c/ios/opengl-surface-options/IAMultisample+iOS.m modules/common/opengl-renderer/c/ios/opengl-surface-options/IAStencilFormat+iOS.m)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/common/opengl-renderer/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaopengl_renderer STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaopengl_renderer PUBLIC ${ia_include_dirs})
	target_link_libraries(iaopengl_renderer iaclib iamulti_touch iaopengl)
	target_generate_generics(iaopengl_renderer include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



# --------------  Modules for group "advanced-math"  --------------n

unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/advanced-math/sfmt/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs dependencies/SFMT-src-1.5.1)
list(APPEND ia_source_c_files dependencies/SFMT-src-1.5.1/SFMT.c)
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iasfmt STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iasfmt PUBLIC ${ia_include_dirs})
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/advanced-math/random-number-generator/c/shared)
list(APPEND iarandom_number-generator_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/advanced-math/random-number-generator/c/shared/IARandomNumberGenerator.h)
list(APPEND ia_source_c_files modules/advanced-math/random-number-generator/c/shared/IARandomNumberGenerator.c)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/advanced-math/random-number-generator/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iarandom_number-generator STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iarandom_number-generator PUBLIC ${ia_include_dirs})
	target_link_libraries(iarandom_number-generator iaclib iasfmt)
	target_generate_generics(iarandom_number-generator include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



# --------------  Modules for group "utilities"  --------------n

unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/utilities/date/c/shared)
list(APPEND iadate_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/utilities/date/c/shared/IADate+Native.h modules/utilities/date/c/shared/IADate.h)
list(APPEND ia_source_c_files modules/utilities/date/c/shared/IADate.c)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/utilities/date/c/android)
	list(APPEND ia_source_c_files modules/utilities/date/c/android/IADate.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/utilities/date/c/ios)
	list(APPEND ia_source_c_files modules/utilities/date/c/ios/IADate.m)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/utilities/date/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iadate STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iadate PUBLIC ${ia_include_dirs})
	target_link_libraries(iadate iaclib)
	target_generate_generics(iadate include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/utilities/url/c/shared)
list(APPEND iaurl_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/utilities/url/c/shared/IAShare.h modules/utilities/url/c/shared/IAUrl.h)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/utilities/url/c/android)
	list(APPEND ia_source_c_files modules/utilities/url/c/android/IAShare.c modules/utilities/url/c/android/IAUrl.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/utilities/url/c/ios)
	list(APPEND ia_source_c_files modules/utilities/url/c/ios/IAShare.m modules/utilities/url/c/ios/IAUrl.m)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/utilities/url/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iaurl STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iaurl PUBLIC ${ia_include_dirs})
	target_link_libraries(iaurl iaopengl)
	target_generate_generics(iaurl include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



# --------------  Modules for group "misc"  --------------n

unset(ia_include_dirs)
unset(ia_source_h_files)
unset(ia_source_c_files)
list(APPEND ia_include_dirs modules/misc/bundle-info/c/shared)
list(APPEND iabundle_info_doxygen_source_dirs ${ia_include_dirs})
list(APPEND ia_source_h_files modules/misc/bundle-info/c/shared/IABundleInfo.h)
if(${IA_PLATFORM} STREQUAL android)
	list(APPEND ia_include_dirs modules/misc/bundle-info/c/android)
	list(APPEND ia_source_c_files modules/misc/bundle-info/c/android/IABundleInfo.c)
endif()
if(${IA_PLATFORM} STREQUAL ios)
	list(APPEND ia_include_dirs modules/misc/bundle-info/c/ios)
	list(APPEND ia_source_c_files modules/misc/bundle-info/c/ios/IABundleInfo.m)
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules/misc/bundle-info/c FILES ${ia_source_h_files} ${ia_source_c_files})
list(APPEND ia_include_dirs include/${IA_PLATFORM}/generated)

if (ia_source_c_files)
	add_library(iabundle_info STATIC ${ia_source_h_files} ${ia_source_c_files})
	target_include_directories(iabundle_info PUBLIC ${ia_include_dirs})
	target_link_libraries(iabundle_info iaclib)
	target_generate_generics(iabundle_info include/${IA_PLATFORM}/generated)
	install(FILES ${ia_source_h_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/${IA_PLATFORM})
endif()



unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_source_dirs ${iaclib_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nclib" "-Gcommon" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_source_dirs ${iamathlib_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/mathlib_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nmathlib" "-Gcommon" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iainput_output_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/input-output_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Ninput-output" "-Gcommon" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/input-output_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iainput_output_doxygen_source_dirs})
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/mathlib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iamathlib_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iaopengl_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nopengl" "-Gcommon" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaopengl_doxygen_source_dirs})
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iamulti_touch_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/multi-touch_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nmulti-touch" "-Gcommon" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/multi-touch_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iamulti_touch_doxygen_source_dirs})
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaopengl_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iaopengl_renderer_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl-renderer_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nopengl-renderer" "-Gcommon" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iabundle_info_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/bundle-info_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nbundle-info" "-Gmisc" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iadate_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/date_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Ndate" "-Gutilities" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaopengl_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iaurl_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/url_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nurl" "-Gutilities" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_source_dirs)
unset(ia_include_dirs)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_include_dirs ${iaclib_doxygen_source_dirs})
list(APPEND ia_source_dirs ${iarandom_number-generator_doxygen_source_dirs})
list(TRANSFORM ia_source_dirs PREPEND "-S${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM ia_include_dirs PREPEND "-I${CMAKE_CURRENT_SOURCE_DIR}/")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/random-number-generator_moduledesc_generated.h
	COMMAND perl GenerateGenericsMain.pl "-Nrandom-number-generator" "-Gadvanced-math" "-D${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/generated" ${ia_source_dirs} ${ia_include_dirs}
	DEPENDS ${ia_dep_files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/perl/generate-generics
)
unset(ia_dep_files)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/clib_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/mathlib_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/input-output_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/multi-touch_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/opengl-renderer_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/bundle-info_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/date_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/url_moduledesc_generated.h)
list(APPEND ia_dep_files ${CMAKE_CURRENT_SOURCE_DIR}/include/doxygen/random-number-generator_moduledesc_generated.h)
add_custom_target(
	doxygen_docs
	COMMAND doxygen doxygen.cmake.cfg
	DEPENDS ${ia_dep_files}	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)

