import io.vacco.shax.logging.ShOption;
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
        // TODO init, test, free
      } else {
        log.info("CI/CD build. Stopping.");
      }
    });
  }
}
