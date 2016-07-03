package sdu.embedded.Sonic.client;

public interface ICoreStateCallback {

    void onCoreReady();

    void onNoisy();

    void onCoreFail();

    void onNormal();

    boolean onSelectSonic(int index);

    String getChoice();

    void writesucc();
}
