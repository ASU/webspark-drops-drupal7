/**
 * ASU Department List Item Component
 */
module.exports = React.createClass({
  handleItemRemove: function(event) {
    this.props.onRemoveDept(this);
  },

  render: function() {
    return <li ref="dept">
      {this.props.title}
      {this.renderSubdeptsLabel()}
      <span className="tag remove">
        <span
          onClick={this.handleItemRemove}
          className="fa fa-close" />
      </span>
    </li>
  },

  renderSubdeptsLabel: function() {
    if (this.props.subdepts) {
      return <span className="tag subdepts">+subdepts</span>
    }
  }
});
