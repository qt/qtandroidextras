//! [Working with lists]
QStringList getTrackTitles(const QJNIObject &album) {
    QStringList stringList;
    QJNIObject list = album.callObjectMethod<jobject>("getTitles",
                                                      "()Ljava/util/List;");

    if (list.isValid()) {
        const int size = list.callMethod<jint>("size");
        for (int i = 0; i < size; ++i) {
            QJNIObject title = list.callObjectMethod<jobject>("get", "(I)Ljava/lang/Object;", i);
            stringList.append(title.toString());
        }
    }
    return stringList;
}
//! [Working with lists]

//! [QJNIObject scope]
void function()
{
    QString helloString("Hello");
    jstring myJString = 0;
    {
        QJNIObject string = QJNIObject::fromString(string);
        myJString = string.object<jstring>();
    }

   // Ops! myJString is no longer valid.
}
//! [QJNIObject scope]
