/**
 * ASU Department Picker Component
 */
var DeptTree = require('./dept-tree');
var DeptList = require('./dept-list');
var Modal = require('./modal');


module.exports = React.createClass({

  componentDidMount: function() {
    this.setSelectedDepartments();
  },

  getInitialState: function() {
    var default_config = {
      items: this.props.items || [],
      options: this.props.options || {}
    }

    return {
      config: default_config,
      selectedDepartments: [],
      currentNode: null,
      includeSubdepts: false
    };
  },

  render: function() {
    return <div className="widget-asu-dept-picker">
      {this.renderBrowseButton()}
      {this.renderDepartmentList()}
      {this.renderModal()}
    </div>
  },

  renderModal: function() {
    var deptTree = <DeptTree 
      ref="deptTree"
      treeData={this.props.tree_json_data}
      showOnly={this.props.showOnly || []}
      onTreeSelect={this.handleDeptTreeSelect}
    />

    return <Modal
      ref="modal"
      title="Select Department"
      content={deptTree}
      onSuccess={this.handleModalSuccess}
      onSubdeptClick={this.handleSubdeptClick}
    />;
  },

  renderDepartmentList: function() {
    return <DeptList
      ref="deptList"
      onRemoveDept={this.handleRemoveDept}
      items={this.state.selectedDepartments}
    />
  },

  renderBrowseButton: function() {
    return <div className="browse-button">
      <input type="button"
        value="Browse"
        className="form-submit"
        onClick={this.handleBrowseClick}
      />
    </div>
  },

  handleRemoveDept: function(doomed) {
    var dept_id = doomed.props.id;
    var config = this.state.config;

    config.items = config.items.filter(function(item){
      return (dept_id != item.dept_id);
    });

    delete config.options[dept_id];

    this.setState({ config: config });
    this.setSelectedDepartments();
  },

  handleSubdeptClick: function() {
    this.setState({ includeSubdepts: !this.state.includeSubdepts });
  },

  handleModalSuccess: function() {
    if (this.state.currentNode) {
      // setup config
      this.setDeptConfig(this.state.currentNode);

      // update selected departments list
      this.setSelectedDepartments();
    }
  },

  handleBrowseClick: function(event) {
    this.refs.modal.show();
  },

  handleDeptTreeSelect: function(data) {
    this.setState({ currentNode: data.node });
  },

  setSelectedDepartments: function() {
    var deptTree = this.refs.deptTree;
    var config = this.state.config;
    var depts = [];

    config.items.map(function(item, index){
      if (!item.tid) {
        node = deptTree.findRootDept(item.dept_nid);
        item.tid = node.tid;
      }

      depts.push({
        id: item.dept_id,
        title: deptTree.getDeptPath(item.tid),
        subdepts: config.options[item.dept_id].subdepts
      });
    });

    this.setState({ selectedDepartments: depts });
    this.triggerChange();
  },

  setDeptConfig: function(data) {
    // get the tree path to set the label
    var config = this.state.config;

    var unique = true;
    config.items.map(function(item, index) {
      if (item.dept_nid == data.dept_nid) {
        unique = false;
        config.options[item.dept_id].subdepts = this.state.includeSubdepts;
      }
    }.bind(this));

    if (unique) {
      config.items.push({
        'dept_id': data.dept_id,
        'dept_nid': data.dept_nid,
        'tree_nids': data.tree_nids,
        'tid': data.tid
      });

      config.options[data.dept_id] = {
        subdepts: this.state.includeSubdepts
      };
    }

    this.setState({ config: config });
  },

  triggerChange: function() {
    if (this.props.onChange) {
      this.props.onChange(this.state.config);
    }
  }
});
