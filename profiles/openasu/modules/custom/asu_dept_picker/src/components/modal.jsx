/**
 * Department Tree Component
 */
var DeptTree = require('./dept-tree');

module.exports = React.createClass({
  componentDidMount: function() {
    document.addEventListener('keyup', function(e) {
      if (e.keyCode == 27) {
        this.hide();
      }
    }.bind(this));
  },

  getInitialState: function() {
    return {
      open: false
    }
  },

  render: function() {

    var modalClass = (this.state.open ? 'dialog-open' : '');

    return <div className={"asu-dept-picker-modal " + modalClass}>
      <div className="dialog">
        <div className="dialog-title">
          {this.props.title}
          <div className="close-dialog" onClick={this.handleCancelClick}>
            <span className="fa fa-close"></span>
          </div>
        </div>
        {this.props.content}
        <div className="actions">
          <div className="form-item form-type-checkbox">
            <input 
              ref="include_subdept"
              type="checkbox"
              className="form-checkbox"
              onClick={this.handleSubdeptClick}
              defaultChecked={this.state.includeSubdepts ? 'checked' : ''}
            /> 
            <label className="option" onClick={this.handleLabelClick}> Include sub-departments?</label>
            <div className="description" style={{'display': 'none'}}>
              This will include all sub-departments beneath the selected department.
            </div>
          </div>
          <input type="button"
            className="form-submit"
            onClick={this.handleSubmitClick}
            value="Submit"
          />
          <input type="button"
            className="form-submit"
            onClick={this.handleCancelClick}
            value="Cancel"
          />
        </div>
      </div>
    </div>
  },

  handleSubdeptClick: function() {
    if (this.props.onSubdeptClick) {
      this.props.onSubdeptClick();
    }
  },

  handleLabelClick: function() {
    this.refs.include_subdept.click();
  },

  handleCancelClick: function() {
    if (this.props.onCancelClick) {
      this.props.onCancelClick();
    }

    this.hide();
  },

  handleSubmitClick: function() {
    if (this.props.onSuccess) {
      this.props.onSuccess();
    }

    this.hide();
  },

  show: function() {
    this.setState({ open: true });
  },

  hide: function() {
    this.setState({ open: false });
  }
});