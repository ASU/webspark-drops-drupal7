(function asu_rfi_responsive() {

    /* -- Main thread -- */
    function main() {
        bindLocation();
        bindPrograms();
        futureRemoval();
        buildBoundCountry();
    }

    /* -- If there is only one item, automatically select it -- */
    function setDefaultSingle(count) {
        if (count == 1) {
            var selectList = document.getElementById('edit-program-code');
            selectList.selectedIndex = 1;
            selectList.firstChild.style.display = 'none';
        }
    }

    /* -- Bind the Online/Offline Selection -- */
    function bindLocation() {
        var online = document.getElementById('edit-location-online');
        var oncampus = document.getElementById('edit-location-on-campus');
        var either = document.getElementById('edit-location-no-preference');
        online.addEventListener('change', function () {
            restoreAllCampuses();
            restoreAllPrograms();
            filterPrograms(this.value);
            setRequired(true);
            checkAddressArea();
            futureRemoval(true);
        }, true);
        oncampus.addEventListener('change', function () {
            restoreAllCampuses();
            restoreAllPrograms();
            filterPrograms(this.value);
            dropOnline();
            setRequired(false);
            checkAddressArea();
            futureRemoval(false);
        }, true);
        either.addEventListener('change', function () {
            restoreAllCampuses();
            restoreAllPrograms();
            filterPrograms(this.value);
            setRequired(false);
            checkAddressArea();
            futureRemoval(false);
        }, true);
    }

    function setRequired(val) {
        var form = document.getElementById("asu-rfi-long-form-data");
        var grad = form.querySelector('input[value=graduate_longform]');
        if (!grad) {
            var label = form.querySelector('label[for=edit-program-code]');

            var reqd = '<span class="form-required">*</span>';
            if (val && label.innerHTML.indexOf(reqd) < 0) {
                label.innerHTML = label.innerHTML + reqd;
            } else if (label.innerHTML.indexOf(reqd) > 0) {
                label.innerHTML = label.innerHTML.replace(reqd, '');
            }
        }
    }

    function futureRemoval(val) {
        var form = document.getElementById("asu-rfi-long-form-data");
        var grad = form.querySelector('input[value=graduate_longform]');
        if (val || grad || document.getElementById('edit-location-online').checked) {
            document.querySelectorAll('.form-item-student-type')[0].setAttribute('style', 'display:none;');
        } else {
            document.querySelectorAll('.form-item-student-type')[0].setAttribute('style', '');
        }
    }

    /* -- Bind the program selector to control what campuses show up -- */
    function bindPrograms() {

        var reg = document.getElementById('edit-program-code');
        reg.addEventListener('change', function () {
            restoreAllCampuses();
            filterCampus(reg.value);
        }, true);
    }

    /* -- Reenable all programs for re-filtering -- */
    function restoreAllPrograms() {
        var select = document.getElementById('edit-program-code');
        var options = select.childNodes;
        select.selectedIndex = 0;
        for (var i = 0; i < options.length; i++) {
            options[i].removeAttribute('style');
            options[i].removeAttribute('disabled');
        }
    }

    /* -- Filter available Programs based on chosen Location -- */
    function filterPrograms(loc) {
        var degrees = Drupal.settings.asu_rfi.degrees;
        for (var i = 0; i < degrees.length; i++) {
            var locations = degrees[i].locations;
            var status = true;
            for (var k = 0; k < locations.length; k++) {
                var location = locations[k].value.toLowerCase();

                if (loc == 'no_preference') {
                    status = false;
                } else if (loc == 'online' && loc == location) {
                    status = false;
                } else if (loc == 'on_campus' && location !== 'online') {
                    status = false;
                }
            }
            if (status) {
                var option = document.getElementById('edit-program-code').querySelector('option[value=' + degrees[i].code + ']');
                option.setAttribute('style', 'display:none;');
                option.setAttribute('disabled', 'disabled');
            }
        }
    }

    /* -- Hide the online campus when onCampus is selected -- */
    function dropOnline() {
        var campusSelect = document.getElementById('edit-campus');
        var campuses = campusSelect.childNodes;
        for (var i = 0; i < campuses.length; i++) {
            var campus = campuses[i];
            if (campus.text.toLowerCase() == 'online') {
                campus.setAttribute('style', 'display: none;');
                campus.setAttribute('disabled', 'disabled');
            }
        }
    }

    /* -- Filter available campuses based on chosen program -- */
    function filterCampus(reg) {
        if (reg) {
            var campusSelect = document.getElementById('edit-campus');
            var campuses = campusSelect.childNodes;
            var degrees = Drupal.settings.asu_rfi.degrees;
            var oncampus = false;
            var either = false;
            if (document.getElementById('edit-location-on-campus').checked) {
                oncampus = true;
            }
            if (document.getElementById('edit-location-no-preference').checked) {
                either = true;
            }
            for (var i = 0; i < degrees.length; i++) {
                var degree = degrees[i];

                if (degree.code == reg) {
                    for (var k = 0; k < campuses.length; k++) {
                        var location = campuses[k];
                        var status = true;
                        for (var p = 0; p < degree.locations.length; p++) {
                            var degLoc = degree.locations[p].value;
                            if (degLoc == location.text || k == 0) {
                                status = false;
                            }
                            if (location.text.toLowerCase() == 'online' && oncampus == true) {
                                status = true;
                            }
                            if (location.text.toLowerCase() == 'online' && either == true) {
                                status = false;
                            }

                        }
                        if (status) {
                            location.setAttribute('style', 'display: none;');
                            location.setAttribute('disabled', 'disabled');
                        }
                    }
                }
            }

        }
    }

    /* -- Restore all campuses for re-filtering -- */
    function restoreAllCampuses() {
        var campuses = document.getElementById('edit-campus');
        var options = campuses.childNodes;
        campuses.selectedIndex = 0;
        for (var i = 0; i < options.length; i++) {
            options[i].removeAttribute('style');
            options[i].removeAttribute('disabled');
        }
    }

    function checkAddressArea() {
        var onlineRadio = document.getElementById('edit-location-online');
        var country = document.getElementById('rfi-country');
        if (onlineRadio.checked || !(country.options[country.selectedIndex].text == "United States" || country.options[country.selectedIndex].text == "Canada")) {
            document.getElementById('edit-address-info').setAttribute('style', 'display: none;');
        } else {
            document.getElementById('edit-address-info').setAttribute('style', 'display: block;');
        }
    }

    function buildBoundCountry() {
        var onlineRadio = document.getElementById('edit-location-online');
        var country = document.getElementById('rfi-country');
        var unbound = country.cloneNode(true);
        var addressArea = document.getElementById('edit-address-info');
        addressArea.setAttribute('style', 'display: none;');
        unbound.id = 'rfi-bound-country';
        unbound.name = '';
        unbound.setAttribute('disabled', 'disabled');
        country.addEventListener('change', function () {

            var index = country.selectedIndex;

            document.getElementById('rfi-bound-country').selectedIndex = index;

            if (!onlineRadio.checked && (country.options[country.selectedIndex].text == "United States" || country.options[country.selectedIndex].text == "Canada")) {
                addressArea.setAttribute('style', 'display: block;');
            } else if (onlineRadio.checked || !(country.options[country.selectedIndex].text == "United States" || country.options[country.selectedIndex].text == "Canada")) {
                addressArea.setAttribute('style', 'display: none;');
            }

        }, true);

        addressArea.getElementsByClassName('fieldset-wrapper')[0].insertBefore(unbound, addressArea.getElementsByClassName('fieldset-wrapper')[0].childNodes[0]);


    }

    /* -- verify that everything is properly loaded before running the main thread -- */
    var checkReady = setInterval(function () {
        try {
            var ch = document.getElementById('edit-program-code');
            if (ch) {
                clearMe();
                main();
            }
        } catch (e) {
        }
    }, 300);
    // Cleans up the CheckReady Interval
    var clearMe = function () {
        clearInterval(checkReady);
    }
})();
