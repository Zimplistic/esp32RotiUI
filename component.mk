COMPONENT_DEPENDS := freertos lcd

COMPONENT_ADD_INCLUDEDIRS += include
COMPONENT_PRIV_INCLUDEDIRS +=  src/screens

ifdef CONFIG_LCD_TEST_ENABLE
COMPONENT_SRCDIRS += src src/screens src/assets/fonts src/assets/images
endif
