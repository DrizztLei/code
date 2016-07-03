package sdu.embedded.Sonic.install;

import java.io.File;
import java.io.IOException;

import sdu.embedded.Sonic.client.DolphinCoreVariables;
import sdu.embedded.Sonic.install.ShellUtils.CommandResult;
import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

public class Installer {

    static String CPU_ABI;
    static final String TAG = "PluginInstaller";

    static {
        if (android.os.Build.CPU_ABI.startsWith("arm"))
            CPU_ABI = "armeabi";
        else CPU_ABI = android.os.Build.CPU_ABI;
    }

    public static File installRoot() throws IOException {
        File root = new File(DolphinCoreVariables.DOLPHIN_HOME);
        if (root.exists()) {
            FileUtils.deleteFile(root);
        }
        if (!root.mkdir()) {
            Log.i(TAG, "mkdir()");
        }
        return root;
    }

    public static void installPlugin(AssetManager am, File root) throws IOException {
        String[] strings = am.list("");
        for (int i = 0; i < strings.length; i++) {
            Log.i(TAG, strings[i]);
        }
        Log.i(TAG, "install " + CPU_ABI);
        FileUtils.copy(am.open("install.sh"), root, "install.sh");
        FileUtils.copy(am.open("uninstall.sh"), root, "uninstall.sh");
        FileUtils.copy(am.open("dolphincall_libs/" + CPU_ABI + "/dolphincall"), root, "dolphincall");
        FileUtils.copy(am.open("dolphinget_libs/" + CPU_ABI + "/dolphinget"), root, "dolphinget");
        FileUtils.copy(am.open("dolphinsu_libs/" + CPU_ABI + "/dolphinsu"), root, "dolphinsu");
    }

    public static void installScripts(AssetManager am, File root) throws IOException {
        File modelsRoot = new File(root, "scripts");
        if (modelsRoot.exists() && modelsRoot.isFile()) {
            modelsRoot.delete();
            modelsRoot.mkdir();
        } else {
            modelsRoot.mkdir();
        }
        File last_events = new File(modelsRoot, "last_events");
        if (!last_events.exists()) last_events.createNewFile();//TODO dummy

    }

    public static void installModel(AssetManager am, File root) throws IOException {
        File modelsRoot = new File(root, "models");
        if (modelsRoot.exists() && modelsRoot.isFile()) {
            modelsRoot.delete();
            modelsRoot.mkdir();
        } else {
            modelsRoot.mkdir();
        }
        String[] models = am.list("models");
        for (int i = 0; i < models.length; i++) {
            Log.i(TAG, models[i]);
            FileUtils.copy(am.open("models/" + models[i]), modelsRoot, models[i]);
        }
    }

    public static boolean installAll(Context ctx) {

        File root = null;
        try {
            root = installRoot();
        } catch (IOException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
            return false;
        }

        AssetManager am = ctx.getAssets();
        try {
            installPlugin(am, root);
            installScripts(am, root);
            installModel(am, root);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        ShellUtils shell = new ShellUtils();

        CommandResult result = shell.execCommand(
                "sh " + DolphinCoreVariables.DOLPHIN_HOME + "install.sh",
                ShellUtils.COMMAND_SU);
        for (int i = 0; i < result.successMsg.size(); i++) {
            Log.i(TAG, "successMsg:" + result.successMsg.get(i));
        }
        for (int i = 0; i < result.errorMsg.size(); i++) {
            Log.i(TAG, "errorMsg:" + result.errorMsg.get(i));
        }
        Log.i(TAG, "result: " + result.result);
        return true;
    }


    public static boolean uninstallAll() {
        ShellUtils shell = new ShellUtils();
        CommandResult result = shell.execCommand(
                "sh " + DolphinCoreVariables.DOLPHIN_HOME + "uninstall.sh",
                ShellUtils.COMMAND_SU);
        for (int i = 0; i < result.successMsg.size(); i++) {
            Log.i(TAG, "successMsg:" + result.successMsg.get(i));
        }
        for (int i = 0; i < result.errorMsg.size(); i++) {
            Log.i(TAG, "errorMsg:" + result.errorMsg.get(i));
        }
        Log.i(TAG, "result: " + result.result);
        return true;
    }
}
