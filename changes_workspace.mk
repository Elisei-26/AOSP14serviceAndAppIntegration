PRODUCT_MODEL := sdk_car_x86_64

DEVICE_PACKAGE_OVERLAYS += device/workspace/overlays 
BOARD_SEPOLICY_DIRS += device/workspace/sepolicy \
						device/workspace/sepolicy/example_service \

PRODUCT_PACKAGES += example_service \
					example.service.manager \
					deviceTemperature \

DEVICE_MANIFEST_FILE += device/workspace/manifests/manifest.xml

DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE += device/workspace/manifests/framework_compatibility_matrix.xml