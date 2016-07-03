package sdu.embedded.Sonic.echo;

/**
 * Created by yqf on 6/30/14.
 */
class UltrasonicData {
    int numSamples;
    byte[] gen;

    UltrasonicData(int n, byte[] g) {
        numSamples = n;
        gen = g;
    }
}
