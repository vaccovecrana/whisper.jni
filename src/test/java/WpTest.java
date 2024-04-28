import io.vacco.shax.logging.ShOption;
import io.vacco.whisper.Wp;
import j8spec.annotation.DefinedOrder;
import j8spec.junit.J8SpecRunner;
import org.junit.runner.RunWith;
import org.slf4j.*;

import java.awt.*;

import static j8spec.J8Spec.*;

@DefinedOrder
@RunWith(J8SpecRunner.class)
public class WpTest {

  static {
    ShOption.setSysProp(ShOption.IO_VACCO_SHAX_DEVMODE, "true");
  }

  private static final Logger log = LoggerFactory.getLogger(WpTest.class);

  static {
    it("Performs inference using an RWKV model", () -> {
      if (!GraphicsEnvironment.isHeadless()) {
        Wp.initNative();
        var wCtx = Wp.initWhisper("/home/jjzazuet/Desktop/ggml-tiny.en.bin", true, 0, true, "WHISPER_AHEADS_TINY_EN");
        Wp.registerProgressCallback((contextPointer, statePointer, progress) -> {
          log.info("Momo! {}", progress);
        });
        Wp.clearGlobalReferences();
        Wp.freeWhisper(wCtx);
      } else {
        log.info("CI/CD build. Stopping.");
      }
    });
  }
}
