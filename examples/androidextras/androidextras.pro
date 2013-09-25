TEMPLATE = subdirs
android {
    qtHaveModule(declarative) {
        SUBDIRS += notification
        EXAMPLE_FILES += notification
    }
}
