package io.vacco.whisper;

public class Wp {

  public static void initNative() {
    var os = String.format("%s-%s", System.getProperty("os.name"), System.getProperty("os.arch"));
    switch (os) {
      case "momo-x64":
        WpNative.loadLibraryFromJar("/some/lib.so");
      default:
        var msg = String.format("No native binaries available for [%s]. PRs are welcome :)", os);
        throw new UnsupportedOperationException(msg);
    }
  }

}