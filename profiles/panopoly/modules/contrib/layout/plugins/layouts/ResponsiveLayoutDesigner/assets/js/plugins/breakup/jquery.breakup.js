/*jslint bitwise: true, eqeqeq: true, immed: true, newcap: true, nomen: false,
 onevar: false, plusplus: false, regexp: true, undef: true, white: false, indent: 2
 browser: true */

/*global window: true define: true jQuery: true */

/**
 * A jQuery plugin.
 *
 * Register arbitrary functions to be fired against jQuery objects when
 * specified break points are entered.
 *
 * Author: Jesse Renee Beach
 * Author URI: http://qemist.us
 * Author Twitter: @jessebeach
 * Author Github: https://github.com/jessebeach
 *
 */

// The plugin factory function.
(function ($) {
  var pluginName = 'BreakUp';
  var $ = jQuery;
  // plugin defaults
  var defaults = {
    'breakpoints': {
      '0': $.noop
    },
    'options': {
      'namespace': pluginName
    }
  };
  // Add the plugin as a property of the jQuery fn object.
  $[pluginName] = (function () {
    // Functions for manipulating the arguments variable.
    var shift = Array.prototype.shift;
    var unshift = Array.prototype.unshift;
    var slice = Array.prototype.slice;
    var splice = Array.prototype.splice;
    /**
     * Build a new BreakUp object.
     */
    function BreakUp() {
      this.currentBreak = undefined;
      this.breakPoints = {};
      this.updated = false;
      this.namespace = pluginName;
      this.$elements = $();
      // Initialize the plugin instance.
      this.initialize.apply(this, arguments);
    }
     
    BreakUp.prototype.initialize = function (breakpoints, options, selector) {
      var bp, opts, fn;
      // Determine if breakpoints were passed in. If not, return, there's nothing to do.
      if (typeof breakpoints === 'string' || (typeof breakpoints === 'object' && 'jquery' in breakpoints)) {
        this.log('[' + pluginName + '] No breakpoints were provided for BreakUp to act on.', 'info');
        return;
      }
      // Merge user options with default options.
      bp = $.extend({}, defaults.breakpoints, breakpoints);
      // Strip the breakpoints from the arguments list.
      shift.call(arguments);
      // Unshift the merged breakpoints back into the arguments.
      unshift.call(arguments, bp);
      // Options is a jquery object or selector
      if ((typeof options === 'object' && 'jquery' in options) || typeof options === 'string') {
        // Slip an undefined into the arguments where the options should be.
        splice.call(arguments, 1, 0, undefined);
      }
      // Process the options.
      if (options) {
        opts = $.extend({}, defaults.options, options);
        this.namespace = opts.namespace;
        // More options to come...
      }
      // A selector is necessary to create a context. It cannot be empty. First check
      // for a string selector.
      if (typeof selector === 'string' || selector === window || selector === document) {
        this.$elements = $(selector);
        // If the selector was provided as something other than a jQuery obejct,
        // we need to replace the corresponding argument with the jQuery selector version.
        splice.call(arguments, 2, 1, this.$elements);
      }
      // Then check for a jQuery object. 
      else if (typeof selector === 'object' && 'jquery' in selector) {
        this.$elements = selector;
      }
      // If the selector matched nothing, error out.
      if (this.$elements.length === 0) {
        this.log('[' + pluginName + '] Neither a jQuery object nor a valid selector were provided for BreakUp to act on.', 'info');
        return;
      }
      // The arguments should only contain the breakpoints, the context elements,
      // and additional arguments for the callbacks from this point on.
      // The options are needed only for initialization, so we remove them.
      splice.call(arguments, 1, 1);
      this.registerBreakPoints.apply(this, arguments);
      // Register a handler on the window resize and load events.
      fn = this.buildProxy(this.breakCheck, this);
      $(window).bind('resize' + '.' + this.namespace, fn);
      $(window).bind('load' + '.' + this.namespace, fn);
    };
    /**
     * Given an object of breakpoint properties and functions associated with those properties,
     * store them internally for reference later.
     */
    BreakUp.prototype.registerBreakPoints = function (breakpoints) {
      var bps = breakpoints;
      var br;
      var index;
      if (typeof bps === 'object') {
        // Remove the breakpoints from the arguments array.
        shift.call(arguments);
        // Loop through the breakpoints.
        for (br in bps) {
          if (bps.hasOwnProperty(br)) {
            if (isNaN(br) && br !== 'default') {
              this.log('[' + pluginName + '] The breakpoint property name \"' + br + '\" is not valid. The property must convert to a number or be the word \"default\".', 'info');
              continue;
            }
            if (typeof bps[br] === 'function') {
              // Represent the default breakpoint as zero internally.
              index = (br === 'default') ? '0': br;
              // Unshift the function into the arguments.
              unshift.call(arguments, bps[br]);
              var args = slice.call(arguments);
              // Build a proxy from the function and store it.
              this.breakPoints[index] = this.buildProxy.apply(this, arguments);
              // Shift the function off the arguments.
              shift.call(arguments);
            }
            else {
              this.log('[' + pluginName + '] ' + bps[br] + ', for the breakpoint ' + br + ' is not a function.', 'info');
            }
          }
        }
      }
    };
    /**
     * Gets the current breakpoint.
     *
     * @return (String) candidate: the number-as-a-string index in the list of breakPoints
     * of the current break point as determined by the screen size.
     */
    BreakUp.prototype.getBreakPoint = function () {
      var br;
      var candidate;
      var screen = this.getScreenWidth();
      for (br in this.breakPoints) {
        if (this.breakPoints.hasOwnProperty(br)) {
          if (Number(br) <= screen && (Number(br) > Number(candidate) || Number(br) === 0)) {
            candidate = br;
          }
        }
      }
      return candidate;
    };
    /**
     * Returns the stored set of breakpoints and their functions.
     */
    BreakUp.prototype.listBreakPoints = function () {
      return this.breakPoints;
    };
     /**
     * Get the current break point and call the function associated with it.
     */
    BreakUp.prototype.breakChangeHandler = function (event) {
      // updated will be set to false when a new breakpoint is encountered.
      if (!this.updated) {
        var callback = this.getBreakPointHandler();
        if (typeof callback === 'function') {
          // Pass the event object through to the callback.
          callback(event);
          this.updated = true;
          return;
        }
        else {
          this.log('[' + pluginName + '] The handler for the current breakpoint is not a function.', 'info');
        }
      }
    };
    /**
     * Get the function associated with a stored breakpoint.
     */
    BreakUp.prototype.getBreakPointHandler = function () {
      return this.breakPoints[this.getBreakPoint()];
    };
    /**
     * Check to see if the screen is in a new breakpoint. Also
     * called on page load.
     */
    BreakUp.prototype.breakCheck = function (event) {
      var br = this.getBreakPoint();
      if (this.currentBreak !== br) {
        // Note the current breakpoint.
        this.currentBreak = br;
        this.updated = false;
        // And do something.
        this.breakChangeHandler(event);
      }
    };
    
    /**
     * Returns a function with 'this' set as the context object.
     *
     * All additional arguments are passed through to the returned function.
     */
    BreakUp.prototype.buildProxy = function (fn, context) {
      var f = fn;
      var c = context;
      // Pull the top two args -- fn and context -- off the arguments array.
      for (var i = 0; i < 2; i++) {
        Array.prototype.shift.call(arguments);
      }
      // Get a local reference to the arguments.
      var args = Array.prototype.slice.call(arguments);
      return function () {
        // Push the callers arguments into the arguments list.
        // This will most likely be an $.Event object.
        for (var i = 0; i < arguments.length; i++) {
          args.unshift(arguments[i]);
        }
        f.apply(c, args);
      };
    };
    /**
    * Get the screen width.
    */
    BreakUp.prototype.getScreenWidth = function () {
      return window.innerWidth || document.documentElement.offsetWidth || document.documentElement.clientWidth;
    };
    /**
     *
     */
    BreakUp.prototype.setNameSpace = function (ns) {
      this.namespace = ns;
    };
    /**
     * 
     */
    BreakUp.prototype.getNameSpace = function () {
      return this.namespace;
    };
  	/**
     * Simple console logging utility that won't blow up in older browsers.
     */
    BreakUp.prototype.log = function (message, type) {
      if ('console' in window) {
        var t = type || 'log';
        console[t](message);
      }
    };
    // Return a new BreakUp object.
    return BreakUp;
  }());
}(jQuery));
