var $ = jQuery;
var _ = require('lodash');

/**
 * Department Tree Component
 */
module.exports = React.createClass({
  getInitialState: function() {
    return {
      treeData: JSON.parse(this.props.treeData),
      currentNode: null
    }
  },

  componentDidMount: function() {
    // initialize tree plugin...
    var el = this.refs.treeContainer;
    var tree_data = this.state.treeData;
    var topLevel = 10;

    var defaults = {
      openAt: 1,
      showOnly: null,
      autoOpen: 0,
      selectable: true
    };
    var options = $.extend(defaults, this.props);

    var show_depts = _.flatten(options.showOnly.map(function(dept_nid){
      return this.getDeptPathIds(dept_nid);
    }.bind(this)));

    options.showOnly = _.uniq(show_depts);

    $(el).tree({
      data: tree_data,
      closedIcon: $('<span class="fa fa-plus-circle"></span>'),
      openedIcon: $('<span class="fa fa-minus-circle"></span>'),

      // First level open
      autoOpen: options.autoOpen,
      selectable: options.selectable,

      // Assign dept_id attribute to each tree <li>
      onCreateLi: function (node, $li) {
        $li.attr('dept_nid', node.dept_nid);
        $li.attr('dept_id', node.dept_id);
        
        if (options.showOnly && Array.isArray(options.showOnly) && options.showOnly.length) {
          $(el).addClass('trimmed');

          $.each(options.showOnly, function(index, item){
            if (item == node.dept_nid || node.dept_id == 'ASU') {
              $li.addClass('visible');
            }
          });
        }

        if (!node.hasChildren()) {
          $li.find('.jqtree-element').prepend('<span class="jqtree-folder-icon fa fa-bookmark"></span>');
        }
      }
    });

    $(el).bind('tree.select', this.onTreeSelect);
  },

  render: function() {
    return <div className="asu-dept-tree">
      <div className="tree-container" ref="treeContainer"></div>
    </div>
  },

  onTreeSelect: function(event) {
    if (event.node) {
      event.node.tree_nids = this.getTreeIds(event.node);
    }

    this.setState({ currentNode: event.node });
    this.props.onTreeSelect(event);
  },

  getDeptPathIds: function(dept_id, id_type, path, reverse) {
    switch (arguments.length) {
      case 1: id_type = 'dept_nid';
      case 2: path = [];
      case 3: reverse = true;
    }

    if (item = this.findRootDept(dept_id, id_type)) {
      path.push(item.dept_nid);

      if (item.parents.length) {
        path = this.getDeptPathIds(item.parents[0], 'tid', path, false);
      }
    }

    if (reverse) {
      path = path.reverse();
    }

    return path;
  },

  getDeptPath: function(dept_tid, path, reverse) {
    switch (arguments.length) {
      case 1: path = [];
      case 2: reverse = true;
    }

    if (item = this.findRootDept(dept_tid, 'tid')) {
      var className = ['fragment'];

      if (item.parents[0] == '0') {
        // abbreviate Arizona State University
        item.name = 'ASU';
        className.push('first');
      }
      if (item.children.length == 0) {
        className.push('last');
      }

      path.push(<span key={dept_tid} className={className.join(' ')}>{item.name}</span>);
      if (item.parents.length) {
        path = this.getDeptPath(item.parents[0], path, false);
      }
    }

    if (reverse) {
      path = path.reverse();
    }

    return path;
  },

  getTreeIds: function(tree, tree_ids) {
    if (arguments.length == 1) {
      tree_ids = [];
    }

    tree_ids.push(tree.dept_nid);

    for (var i = 0; i < tree.children.length; i++) {
      this.getTreeIds(tree.children[i], tree_ids);
    }

    return tree_ids;
  },

  findRootDept: function(dept_id, id_type, data) {
    var dept = null;

    switch(arguments.length) {
      case 1:
        id_type = 'dept_nid';
      case 2:
        data = this.state.treeData;
        break;
    }

    for (var i = 0; i < data.length; i++) {
      if (dept == null && data[i] != null) {
        if (data[i][id_type] == dept_id) {
          return data[i];
        }
        else if (data[i].hasOwnProperty('children')) {
          dept = this.findRootDept(dept_id, id_type, data[i].children);
        }
      }
      else {
        break;
      }
    }
    return dept;
  }
});
