(function asu_rfi_responsive() {

    /* -- Main thread -- */
    function main() {
        bindLocation();
        bindPrograms();
        futureRemoval();
        buildBoundCountry();
    }

    /* -- If there is only one item, automatically select it -- */
  /*
    function setDefaultSingle(count) {
        if (count === 1) {
            let selectList = document.getElementById('edit-program-code');
            selectList.selectedIndex = 1;
            selectList.firstChild.style.display = 'none';
        }
    }
    */

    /* -- Bind the Online/Offline Selection -- */
    function bindLocation() {
        let online = document.getElementById('edit-location-online');
        let oncampus = document.getElementById('edit-location-on-campus');
        let either = document.getElementById('edit-location-no-preference');
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
        let form = document.getElementsByName("asu-rfi-long-form-data");
        let grad = form[0].querySelector('input[value=graduate_longform]');
        if (!grad) {
            let label = form.querySelector('label[for=edit-program-code]');
            let required = '<span class="form-required">*</span>';
            if (val && label.innerHTML.indexOf(required) < 0) {
                label.innerHTML = label.innerHTML + required;
            } else if (label.innerHTML.indexOf(required) > 0) {
                label.innerHTML = label.innerHTML.replace(required, '');
            }
        }
    }

    function futureRemoval(val) {
        let form = document.getElementById("asu-rfi-long-form-data");
        let grad = form.querySelector('input[value=graduate_longform]');
        if (val || grad || document.getElementById('edit-location-online').checked) {
            document.querySelectorAll('.form-item-student-type')[0].setAttribute('style', 'display:none;');
        } else {
            document.querySelectorAll('.form-item-student-type')[0].setAttribute('style', '');
        }
    }

    /* -- Bind the program selector to control what campuses show up -- */
    function bindPrograms() {

        let reg = document.getElementById('edit-program-code');
        reg.addEventListener('change', function () {
            restoreAllCampuses();
            filterCampus(reg.value);
        }, true);
    }

    /* -- Reenable all programs for re-filtering -- */
    function restoreAllPrograms() {
        let select = document.getElementById('edit-program-code');
        let options = select.childNodes;
        select.selectedIndex = 0;
        for (let i = 0; i < options.length; i++) {
            options[i].removeAttribute('style');
            options[i].removeAttribute('disabled');
        }
    }

    /* -- Filter available Programs based on chosen Location -- */
    function filterPrograms(loc) {
        let degrees = Drupal.settings.asu_rfi.degrees;
        for (let i = 0; i < degrees.length; i++) {
            let locations = degrees[i].locations;
            let status = true;
            for (let k = 0; k < locations.length; k++) {
                let location = locations[k].value.toLowerCase();

                if (loc === 'no_preference') {
                    status = false;
                } else if (loc === 'online' && loc === location) {
                    status = false;
                } else if (loc === 'on_campus' && location !== 'online') {
                    status = false;
                }
            }
            if (status) {
                let option = document.getElementById('edit-program-code').querySelector('option[value=' + degrees[i].code + ']');
                option.setAttribute('style', 'display:none;');
                option.setAttribute('disabled', 'disabled');
            }
        }
    }

    /* -- Hide the online campus when onCampus is selected -- */
    function dropOnline() {
        let campusSelect = document.getElementById('edit-campus');
        let campuses = campusSelect.childNodes;
        for (let i = 0; i < campuses.length; i++) {
            let campus = campuses[i];
            if (campus.text.toLowerCase() === 'online') {
                campus.setAttribute('style', 'display: none;');
                campus.setAttribute('disabled', 'disabled');
            }
        }
    }

    /* -- Filter available campuses based on chosen program -- */
    function filterCampus(reg) {
        if (reg) {
            let campusSelect = document.getElementById('edit-campus');
            let campuses = campusSelect.childNodes;
            let degrees = Drupal.settings.asu_rfi.degrees;
            let oncampus = false;
            let either = false;
            if (document.getElementById('edit-location-on-campus').checked) {
                oncampus = true;
            }
            if (document.getElementById('edit-location-no-preference').checked) {
                either = true;
            }
            for (let i = 0; i < degrees.length; i++) {
                let degree = degrees[i];

                if (degree.code === reg) {
                    for (let k = 0; k < campuses.length; k++) {
                        let location = campuses[k];
                        let status = true;
                        for (let p = 0; p < degree.locations.length; p++) {
                            let degLoc = degree.locations[p].value;
                            if (degLoc === location.text || k === 0) {
                                status = false;
                            }
                            if (location.text.toLowerCase() === 'online' && oncampus === true) {
                                status = true;
                            }
                            if (location.text.toLowerCase() === 'online' && either === true) {
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
        let campuses = document.getElementById('edit-campus');
        let options = campuses.childNodes;
        campuses.selectedIndex = 0;
        for (let i = 0; i < options.length; i++) {
            options[i].removeAttribute('style');
            options[i].removeAttribute('disabled');
        }
    }

    function checkAddressArea() {
        let onlineRadio = document.getElementById('edit-location-online');
        let country = document.getElementById('rfi-country');
        if (onlineRadio.checked || !(country.options[country.selectedIndex].text === "United States" || country.options[country.selectedIndex].text === "Canada")) {
            document.getElementById('edit-address-info').setAttribute('style', 'display: none;');
        } else {
            document.getElementById('edit-address-info').setAttribute('style', 'display: block;');
        }
    }

    function buildBoundCountry() {
        let onlineRadio = document.getElementById('edit-location-online');
        let country = document.getElementById('rfi-country');
        let unbound = country.cloneNode(true);
        let addressArea = document.getElementById('edit-address-info');
        addressArea.setAttribute('style', 'display: none;');
        unbound.id = 'rfi-bound-country';
        unbound.name = '';
        unbound.setAttribute('disabled', 'disabled');
        country.addEventListener('change', function () {

            //let index = country.selectedIndex;

            document.getElementById('rfi-bound-country').selectedIndex = country.selectedIndex;

            if (!onlineRadio.checked && (country.options[country.selectedIndex].text === "United States" || country.options[country.selectedIndex].text === "Canada")) {
                addressArea.setAttribute('style', 'display: block;');
            } else if (onlineRadio.checked || !(country.options[country.selectedIndex].text === "United States" || country.options[country.selectedIndex].text === "Canada")) {
                addressArea.setAttribute('style', 'display: none;');
            }

        }, true);

        addressArea.getElementsByClassName('fieldset-wrapper')[0].insertBefore(unbound, addressArea.getElementsByClassName('fieldset-wrapper')[0].childNodes[0]);


    }

    /* -- verify that everything is properly loaded before running the main thread -- */
    let checkReady = setInterval(function () {
        try {
            let ch = document.getElementById('edit-program-code');
            if (ch) {
                clearMe();
                main();
            }
        } catch (e) {
        }
    }, 300);
    // Cleans up the CheckReady Interval
    let clearMe = function () {
        clearInterval(checkReady);
    }
})();
