(function (window, $) {
  var RLD = (function(){
    /**
     * Extend jQuery to smooth out version differences.
     */
    $.Event.prototype.getDelegator = function () {
      if ('delegateTarget' in this) {
        return this.delegateTarget;
      }
      if ('liveFired' in this) {
        return this.liveFired;
      }
      return null;
    };
    // Identify jQuery events from other objects.
    $.Event.prototype.__marker = 'jQueryEvent';
    /**
     * Create the InitClass object that all other objects will extend.
     */
    var InitClass = (function () {

      var plugin = 'InitClass';

      function InitClass() {
        // Don't set anything in here, or all objects will inherit these values.
      }
      /**
       * Safe logging function.
       */
      InitClass.prototype.log = function (message, type) {
        if ('console' in window) {
          var type = type || 'log';
          if (type in console) {
            console[type](message);
          }
        }
      };
      /**
       *
       */
      InitClass.prototype.init = function (opts) {
        // Create a topics property for pub/sub event handling.
        this.topics = {};
        // Process the options for this instance.
        var prop;
        var options = ('options' in this) ? this.options : {};
        options = $.extend({}, options, opts);
        for (prop in options) {
          if (options.hasOwnProperty(prop)) {
            this[prop] = options[prop];
          }
        }
        // Delete the options.
        if ('options' in this) {
          delete this.options;
        }
        // Call the object's setup method.
        this.setup.apply(this);
      };
      /**
       *
       */
      InitClass.prototype.setup = function () {};
      /**
       *
       */
      InitClass.prototype.info = function (property, value) {              
        if (value !== undefined) {
          this[property] = value;
          return;
        }
        if (property in this) {
          return this[property];
        }
        return;
      };
      /**
       *
       */
      InitClass.prototype.build = function (options) {
        return this.$editor;
      };
      /**
       *
       */
      InitClass.prototype.addItem = function (item) {
        this.items.push(item);
      };
      /**
       *
       */
      InitClass.prototype.getItem = function (index) {
        var i;
        for (i = 0; i < this.items.length; i++) {
          for (property in this.items[i]) {
            if ('machine_name' in this.items[i] && this.items[i]['machine_name'] === index) {
                return this.items[i];
            }
          }
        }
        this.log('[RLD | ' + plugin + '] Item not found in this set.', 'info');
        return null;
      };
      /**
       *
       */
      InitClass.prototype.snapshot = function (index) {
        var snapshot = {};
        var prop;
        for (prop in this) {
          if (this.hasOwnProperty(prop)) {
            snapshot[prop] = this[prop];
          }
        }
        return snapshot;
      };
      /**
       *
       */
      InitClass.prototype.topic = function(id) {
        var callbacks;
        var topic = id && this.topics[id];
        if (!topic) {
          callbacks = jQuery.Callbacks('unique');
          topic = {
            publish: function () {
              // Create a jQuery Event for consistency and shift it into the arguments.
              if (!(arguments.length > 0 && typeof arguments[0] === 'object' && '__marker' in arguments[0] && arguments[0].__marker === 'jQueryEvent')) {
                var e = $.Event(id);
                // Unshift in the original target for reference if this event bubbles.
                e.type = id;
                Array.prototype.unshift.call(arguments, e); 
              }
              callbacks.fireWith(this, arguments);
            },
            subscribe: callbacks.add,
            unsubscribe: callbacks.remove
          };
          if (id) {
            this.topics[id] = topic;
          }
        }
        return topic;
      };
      /**
       *
       */
      InitClass.prototype.transferSubscriptions = function (subscribers) {
        var subs = subscribers;
        var topics = this.topics;
        var i, k, top, id, sub;
        if (!('length' in subscribers && subscribers.length > 0)) {
          subs = [subscribers];
        }
        for (i = 0; i < subs.length; i++) {
          sub = subs[i];
          if ('topic' in sub) {
            for (top in topics) {
              if (topics.hasOwnProperty(top)) {
                sub.topic(top).subscribe(this.topic(top).publish); 
              }
            }
          }
        }
      };
      
      return InitClass;
    }());

    /**
     * The ResponsiveLayoutDesigner is a facade for a set of sub-systems that manage
     * the configuration of a responsive layout through a browser.
     */
    function ResponsiveLayoutDesigner() {
      var options = {};
      var plugin = 'ResponsiveLayoutDesigner';
      this.steps = {};
      this.regions = {};
      this.grids = {};
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the RLD with the InitClass.
     */
    ResponsiveLayoutDesigner.prototype = new InitClass();
    /**
     * Provide the InitClass for all other Classes to extend.
     */
    ResponsiveLayoutDesigner.InitClass = InitClass;
    /**
     * Implement the init() interface.
     */
    ResponsiveLayoutDesigner.prototype.setup = function () {
      // Merge in user options.
      var regionList, availableRegionList, stepList, gridList;
      // Create the application root node.
      this.$editor = $('<div>', {
        'class': 'rld-application'
      });
      // Instansiate the LayoutManager.
      // this.regions is a simple object. The RegionList provides methods to
      // manipulate this simple set.
      regionList = new RLD.RegionList();
      availableRegionList = new RLD.RegionList();
      if ('regions' in this) {
        if ('active' in this.regions) {
          regionList.addItem(this.regions.active);
        }
        if ('available' in this.regions) {
          availableRegionList.addItem(this.regions.available);
        }
        delete this.regions;
      }
      else {
        this.log('[RLD | ' + plugin + '] No regions provided.');
      }
      if ('steps' in this) {
        stepList = new RLD.StepList({
          'steps': this.steps
        });
        delete this.steps;
      }
      else {
        this.log('[RLD | ' + plugin + '] No steps provided.');
      }
      if ('grids' in this) {
        gridList = new RLD.GridList({
          'grids': this.grids
        });
        delete this.grids;
      }
      else {
        this.log('[RLD | ' + plugin + '] No grids provided.');
      }
      // Create a layout manager.
      this.layoutManager = new RLD.LayoutManager({
        'stepList': stepList,
        'regionList': regionList,
        'availableRegionList': availableRegionList,
        'gridList': gridList
      });
      // Create a layoutPreviewer.
      this.layoutPreviewer = new RLD.LayoutPreviewer({
        'stepList': stepList,
        'gridList': gridList
      });
      // Define topics that will pass-through.
      this.topic('stepActivated');
      this.transferSubscriptions(this.layoutPreviewer);
      this.topic('regionOrderUpdated');
      this.topic('layoutSaved');
      this.topic('regionAdded');
      this.topic('regionRemoved');
      this.topic('regionResized');
      this.topic('regionResizing');
      this.topic('regionResizeStarted');
      // Transfer pass-through subscriptions.
      this.transferSubscriptions(this.layoutManager);
    };
    /**
     * Generate a view of the class instance.
     *
     * Returns a DOM fragment.
     */
    ResponsiveLayoutDesigner.prototype.build = function () {
      // Build the layoutManager and attach it to the $editor.
      this.layoutManager.build().appendTo(this.$editor);
      // Activate the first step.
      var firstStep = this.layoutManager.stepList.info('items')[0];
      var simpleClick = $.Event('click');
      simpleClick.data = {'manager': this.layoutManager.stepManager};
      this.layoutManager.stepManager.activateStep.call(this.layoutManager.stepManager.info('$editor').find('a:first').get(0), simpleClick);
      return this.$editor;
    };

    ResponsiveLayoutDesigner.prototype.snapshot = function () {
      return this.layoutManager;
    };

    return ResponsiveLayoutDesigner;
    
  }());
  
  // Expose ResponsiveLayoutDesigner to the global object
  return (window.ResponsiveLayoutDesigner = RLD);
}(window, jQuery));
/**
 * supplantClass() jQuery plugin
 *
 * Adds the replacement class string to each element.
 *
 * If a class or classes contain the needle, they are removed from the element.
 */
(function ($) {
	// Add the plugin as a property of the jQuery fn object.
	$.fn['supplantClass'] = function (needle, replacement) {
	  return this.each(function (index, element) {
      var $this = $(this);
      var cl = [];
      // Get an array of classes the excludes any that contain the needle.
      var classes = ($this.attr('class') || '').split(' ');
      for (var i = 0; i < classes.length; i++) {
        if (classes[i].indexOf(needle) === -1) {
          cl.push(classes[i]);
        }
      }
      // Push the replacement in all cases.
      $.merge(cl, replacement.split(' '));
      // Create a string and assign it to the object.
      $this.removeAttr('class').addClass(cl.join(' '));
    });
	};
}(jQuery));
