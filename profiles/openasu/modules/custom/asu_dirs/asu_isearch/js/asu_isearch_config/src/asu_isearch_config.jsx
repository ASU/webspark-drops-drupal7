var Tooltip = React.createClass({
    render: function () {
        return <span className="tooltip-wrap" data-toggle="tooltip" data-placement="right" title={this.props.message}><i
            className="fa fa-question-circle"></i></span>
    }
});

var CheckboxToggle = React.createClass({
    getInitialState: function () {
        return {checked: this.props.checked};
    },
    handleClick: function () {
        this.setState({
            checked: !this.state.checked
        });
    },
    render: function () {
        var tooltip;

        if (this.props.tooltipMessage !== undefined && this.props.tooltipMessage != '') {
            tooltip = <Tooltip message={this.props.tooltipMessage}/>;
        }

        return <div className={"form-type-checkbox form-item-" + this.props.className + " form-item checkbox"}>
            <input
                onClick={this.handleClick}
                type="checkbox" id={this.props.id}
                name={this.props.fieldName}
                defaultChecked={(this.state.checked || this.props.checked) ? 'checked' : ''}
                defaultValue={this.props.value}
                className="form-checkbox tgl tgl-light"/>
            <label htmlFor={this.props.id} className="tgl-btn"></label>
            <div className="fake-label">{this.props.label} {tooltip}</div>
        </div>
    }
});

function initIsearchConfig() {
    var $ = jQuery;

    if (!$(document).data.isearch_config) {
        $(document).data.isearch_config = {};
    }

    $('.asu-isearch-configuration .form-type-checkbox:not([data-reactid])').each(function () {
        var label = $(this).find('label');
        var input = $(this).find('input');
        var targetId = input.attr('id');
        var className = targetId.replace(/^edit-/, '');

        options = {
            id: targetId,
            label: label.text(),
            tooltipMessage: $(this).find('.help-block, .description').text(),
            fieldName: input.attr('name'),
            checked: input.is(':checked'),
            value: input.attr('value'),
            className: className,
        };

        if ($(document).data.isearch_config[targetId]) {
            ReactDOM.unmountComponentAtNode(this);
        }

        var el = React.createElement(CheckboxToggle, options);
        $(document).data.isearch_config[targetId] = el;

        ReactDOM.render(el, this);
    });

    $('.asu-isearch-configuration .form-item:not(.form-type-checkbox) .help-block:not([data-reactid])').each(function () {
        var tooltip_message = $(this).text();
        var label = $(this).siblings('label');

        var el = React.createElement(Tooltip, {message: tooltip_message});
        ReactDOM.render(el, this);

        $(this).appendTo(label);
    });

    // activate tooltips
    $('[data-toggle="tooltip"]').tooltip();
}
