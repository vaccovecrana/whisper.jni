package io.vacco.whisper;

public interface WpNewSegmentCallback {
  void onNewSegment(long contextPointer, long statePointer, int nNew);
}
