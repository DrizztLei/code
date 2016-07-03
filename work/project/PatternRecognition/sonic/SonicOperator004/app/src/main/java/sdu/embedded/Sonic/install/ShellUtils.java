package sdu.embedded.Sonic.install;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;


import android.os.Build;
import android.util.Log;


public class ShellUtils {
    public static final String COMMAND_SU = "su";
    public static String COMMAND_DOLPHIN = "dolphinsu";
    public static final String COMMAND_SH = "sh";
    public static final String COMMAND_EXIT = "exit\n";
    public static final String COMMAND_LINE_END = "\n";
    public boolean loop = true;
    private Process process;

    static {
        if (Build.VERSION.SDK_INT >= 17)
            COMMAND_DOLPHIN = COMMAND_SU;
    }

    /**
     * check whether has root permission
     *
     * @return
     */
    public boolean checkRootPermission() {
        return execCommand("echo root", COMMAND_SU, false, false).result == 0;
    }

    /**
     * execute shell command, default return result msg
     *
     * @param command command
     * @param isRoot  whether need to run with root
     * @return
     * @see ShellUtils#execCommand(String[], boolean, boolean)
     */
    public CommandResult execCommand(String command, String start) {
        return execCommand(new String[]{command}, start);
    }

    /**
     * execute shell commands, default return result msg
     *
     * @param commands command list
     * @param isRoot   whether need to run with root
     * @return
     * @see ShellUtils#execCommand(String[], boolean, boolean)
     */
    public CommandResult execCommand(List<String> commands, String start) {
        return execCommand(commands == null ? null : commands.toArray(new String[]{}), start);
    }

    /**
     * execute shell commands, default return result msg
     *
     * @param commands command array
     * @param isRoot   whether need to run with root
     * @return
     * @see ShellUtils#execCommand(String[], boolean, boolean)
     */
    public CommandResult execCommand(String[] commands, String start) {
        return execCommand(commands, start, true, false);
    }

    /**
     * execute shell command
     *
     * @param command         command
     * @param isRoot          whether need to run with root
     * @param isNeedResultMsg whether need result msg
     * @return
     * @see ShellUtils#execCommand(String[], boolean, boolean)
     */
    public CommandResult execCommand(String command, String start, boolean isNeedResultMsg, boolean isWaiting) {
        return execCommand(new String[]{command}, start, isNeedResultMsg, isWaiting);
    }

    /**
     * execute shell commands
     *
     * @param commands        command list
     * @param isRoot          whether need to run with root
     * @param isNeedResultMsg whether need result msg
     * @return
     * @see ShellUtils#execCommand(String[], boolean, boolean)
     */
    public CommandResult execCommand(List<String> commands, String start, boolean isNeedResultMsg, boolean isWaiting) {
        return execCommand(commands == null ? null : commands.toArray(new String[]{}), start);
    }

    /**
     * execute shell commands
     *
     * @param commands        command array
     * @param isRoot          whether need to run with root
     * @param isNeedResultMsg whether need result msg
     * @return <ul>
     * <li>if isNeedResultMsg is false, {@link CommandResult#successMsg} is null and
     * {@link CommandResult#errorMsg} is null.</li>
     * <li>if {@link CommandResult#result} is -1, there maybe some excepiton.</li>
     * </ul>
     */

    public CommandResult execCommand(String[] commands, String start, boolean isNeedResultMsg, boolean isWaiting) {
        int result = -1;
        if (commands == null || commands.length == 0) {
            return new CommandResult(result, null, null);
        }

        process = null;
        BufferedReader successResult = null;
        BufferedReader errorResult = null;
        List<String> successMsg = null;
        List<String> errorMsg = null;

        DataOutputStream os = null;

        try {
            process = Runtime.getRuntime().exec(start);
            os = new DataOutputStream(process.getOutputStream());
            for (String command : commands) {
                if (command == null) {
                    continue;
                }
                os.write(command.getBytes());
                os.writeBytes(COMMAND_LINE_END);
                os.flush();
            }
            os.writeBytes(COMMAND_EXIT);
            os.flush();

            if (isWaiting && loop)
                process.waitFor();

            // get command result
            if (isNeedResultMsg) {
                successMsg = new LinkedList<String>();
                errorMsg = new LinkedList<String>();
                successResult = new BufferedReader(new InputStreamReader(process.getInputStream()));
                errorResult = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                String s;
                while (loop && (s = successResult.readLine()) != null) {
                    successMsg.add(s);
                    //Log.e("sh", s);
                }
                while (loop && (s = errorResult.readLine()) != null) {
                    errorMsg.add(s);
                    //Log.e("sh", s);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (os != null) {
                    os.close();
                }
                if (successResult != null) {
                    successResult.close();
                }
                if (errorResult != null) {
                    errorResult.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

            if (process != null) {
                process.destroy();
            }
        }
        return new CommandResult(result, successMsg == null ? null : successMsg, errorMsg == null ? null : errorMsg);
    }

    /**
     * result of command
     * <ul>
     * <li>{@link CommandResult#result} means result of command, 0 means normal, else means error, same to excute in
     * linux shell</li>
     * <li>{@link CommandResult#successMsg} means success message of command result</li>
     * <li>{@link CommandResult#errorMsg} means error message of command result</li>
     * </ul>
     *
     * @author <a href="http://www.trinea.cn" target="_blank">Trinea</a> 2013-5-16
     */
    public static class CommandResult {

        /**
         * result of command
         **/
        public int result;
        /**
         * success message of command result
         **/
        public List<String> successMsg;
        /**
         * error message of command result
         **/
        public List<String> errorMsg;

        public CommandResult(int result) {
            this.result = result;
        }

        public CommandResult(int result, List<String> successMsg, List<String> errorMsg) {
            this.result = result;
            this.successMsg = successMsg;
            this.errorMsg = errorMsg;
        }
    }

    public void kill() {
        if (process != null) {
            Log.e("sh", "kill start");
            ProcessUtils.processDestroy(process);
            Log.e("sh", "kill end");
        }
    }
}