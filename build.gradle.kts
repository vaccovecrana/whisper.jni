plugins { id("io.vacco.oss.gitflow") version "0.9.8" }

apply(plugin = "io.vacco.oss.gitflow")
group = "io.vacco.whisper"
version = "1.5.5.0.0.1"

configure<io.vacco.oss.gitflow.GsPluginProfileExtension> {
  addJ8Spec()
  addClasspathHell()
  sharedLibrary(true, false)
}

dependencies {
  testImplementation("io.vacco.shax:shax:1.7.30.0.0.7")
}

tasks.withType<Test> {
  minHeapSize = "512m"
  maxHeapSize = "16384m"
}
