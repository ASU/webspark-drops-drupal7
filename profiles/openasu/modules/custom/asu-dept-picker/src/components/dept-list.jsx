/**
 * ASU Department Picker Component
 */
var DeptListItem = require('./dept-list-item');

module.exports = React.createClass({
  render: function() {
    return <ul className="asu-dept-list">
      {this.renderList()}
    </ul>
  },

  renderList: function() {

    if (this.props.items.length == 0) {
      return <li><span className="list-no-items">Click browse to add department(s)</span></li>;
    }

    return this.props.items.map(function(item) {
      return <DeptListItem
        key={item.id}
        onRemoveDept={this.props.onRemoveDept}
        subdepts={item.subdepts}
        id={item.id}
        title={item.title}
      />
    }.bind(this));
  },
});
