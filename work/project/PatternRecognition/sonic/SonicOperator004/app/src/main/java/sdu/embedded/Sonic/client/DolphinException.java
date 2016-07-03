package sdu.embedded.Sonic.client;

public class DolphinException extends Exception {

    String err = null;

    public DolphinException(String err) {
        this.err = err;
    }

    @Override
    public String getMessage() {
        // TODO Auto-generated method stub
        return err;
    }

}
