var Tooltip = React.createClass({
    displayName: "Tooltip",
    render: function () {
        return React.createElement("span", {
            className: "tooltip-wrap",
            "data-toggle": "tooltip",
            "data-placement": "right",
            title: this.props.message
        }, React.createElement("i", {className: "fa fa-question-circle"}))
    }
});

var CheckboxToggle = React.createClass({
    displayName: "CheckboxToggle",
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
            tooltip = React.createElement(Tooltip, {message: this.props.tooltipMessage});
        }

        return React.createElement("div", {className: "form-type-checkbox form-item-" + this.props.className + " form-item checkbox"},
            React.createElement("input", {
                onClick: this.handleClick,
                type: "checkbox",
                id: this.props.id,
                name: this.props.fieldName,
                defaultChecked: (this.state.checked || this.props.checked) ? 'checked' : '',
                defaultValue: this.props.value,
                className: "form-checkbox tgl tgl-light"
            }),
            React.createElement("label", {htmlFor: this.props.id, className: "tgl-btn"}),
            React.createElement("div", {className: "fake-label"}, this.props.label, " ", tooltip)
        )
    }
});

function initIsearchConfig() {
    var $ = jQuery;

    if (!$(document).data.isearch_config) {
        $(document).data.isearch_config = {};
    }

    //todo: remove?
    $('.asu-isearch-configuration .form-submit').click(function (event) {
        // when saving the asu directory panel
        // replace current state with reset flag, so that the parameter
        // history store widget knows to ignore History.js configs
        var path = window.location.pathname.split('?')[0];
        history.replaceState({reset: true}, document.title, path);
    });

    $('.asu-isearch-configuration .form-type-checkbox:not([data-reactid])')
        .filter(function (index) {
            return $(this).parents('.widget-asu-dept-picker').length === 0;
        }).each(function () {
        var label = $(this).find('label');
        var input = $(this).find('input');
        var targetId = input.attr('id') || '';

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

    $('.asu-isearch-configuration .form-item:not(.form-type-checkbox) .help-block:not([data-reactid])')
        .filter(function (index) {
            return $(this).parents('.widget-asu-dept-picker').length === 0;
        })
        .each(function () {
            var tooltip_message = $(this).text();
            var label = $(this).siblings('label');

            var el = React.createElement(Tooltip, {message: tooltip_message});
            ReactDOM.render(el, this);

            $(this).appendTo(label);
        });

    // activate tooltips
    $('[data-toggle="tooltip"]').tooltip();
}

