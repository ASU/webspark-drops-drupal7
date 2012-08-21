(function (RLD, $) {

  RLD['Region'] = (function () {

    var plugin = 'Region';
    /**
     *
     */
    function Region() {
      this.$editor = $('<div>', {});
      this.type = 'region';
      this.columns = 0; // The number of columns this region consumes in a step.
      this.span = 0; // A temporary column consumption count for rendering a view.
      this.columnClass = 'rld-span_';
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    Region.prototype = new RLD.InitClass();
    /**
     *
     */
    Region.prototype.setup = function () {
      this.span = this.columns;
    };
    /**
     *
     */
    Region.prototype.build = function (options) {
      // @todo this classes stuff needs to be generalized.
      var classes = [];
      var style = {};
      classes.push('rld-' + this.type);
      var fn;
      if (options && 'classes' in options && 'length' in options.classes && options.classes.length > 0) {
        classes = classes.concat(options.classes).join(' ');
      }
      if (options && 'style' in options && typeof options.style === 'object') {
        style = $.extend(style, options.style);
      }
      
      this.$editor = $('<div>', {
        'id': ('label' in this) ? 'rld-region-' + this.label.split(' ').join('_') : '',
        'class': classes,
        'html': $('<div>', {
          'class': 'rld-inner',
          'html': $('<p>', {
            'text': this.label
          })
        })
      })
      .css(style);
      // Save a reference to the model object to data().
      this.$editor
      .data('RLD/Region', this);
    
      return this.$editor;
    };
    /**
     *
     */
    Region.prototype.alterColumns = function (columns, isRelative) {
      if (isRelative) {
        this.columns += Number(columns);
      }
      else {
        this.columns = Number(columns);
      }
      if (this.columns < 0) {
        this.columns = 0;
      }
      // Change the view to match the number of columns.
      this.alterSpan(this.columns);
      // Return the view.
      return this.$editor;
    };
    /**
     *
     */
    Region.prototype.alterSpan = function (span, isRelative) {
      if (isRelative) {
        this.span += Number(span);
      }
      else {
        this.span = Number(span);
      }
      if (this.span < 0) {
        this.span = 0;
      }
      var span = this.columnClass + this.span;
      this.$editor.supplantClass(this.columnClass, span);
      // Return the new span.
      return span;
    };
  
    return Region;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));
