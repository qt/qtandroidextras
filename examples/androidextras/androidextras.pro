TEMPLATE = subdirs

android {
    qtHaveModule(quick) {
        SUBDIRS += \
            notification \
            jnimessenger \
            services

        EXAMPLE_FILES += \
            notification \
            jnimessenger \
            services
    }
}
