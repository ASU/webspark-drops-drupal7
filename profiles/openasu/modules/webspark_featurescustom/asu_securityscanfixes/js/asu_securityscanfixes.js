if (top.frames.length != 0 && document.getElementsByTagName('iframe').length <= 0) {
  top.location = self.document.location;
}