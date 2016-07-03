package sdu.embedded.Sonic.client;

public interface IDolphinStateCallback {
    void onCoreReady();

    void onNoisy();

    void onCoreFail();

    void onNormal();

    String getChoice();

    void writesucc();
}
