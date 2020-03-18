TEMPLATE = subdirs
android {
    qtHaveModule(quick) {
        SUBDIRS += \
            notification \
            jnimessenger

        EXAMPLE_FILES += \
            notification \
            jnimessenger
    }
}
