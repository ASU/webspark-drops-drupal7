<?php

/**
 * ASU Get GDPR Markup - Creates simple HTML to append to end of all RFI forms to ensure GDPR compliance
 *
 * @return string - HTML containing all pertinent information and resources pertaining to GDPR
 */
function asu_libs_get_gdpr_markup() {
  return "\n<div>
        <h5>By completing and submitting your information to ASU, you consent to:</h5>
        <ol class='gdpr-list'>
            <li>ASU using this information to contact you regarding information as you requested</li>
            <li>The terms of <a class='gdpr-link' href='https://www.asu.edu/privacy/#asu-privacy-general'>ASU's Privacy Statement</a></li>
            <li>If you are in the European Union or another country or state that has adopted the GDPR
            (General Data Protection Regulation) or similar privacy protection, please also read the
            <a class='gdpr-link' href='https://www.asu.edu/privacy/#european-union-supplement'>ASU European Supplement to ASU's Privacy Statement</a>
            </li>
        </ol>
    </div>\n";
}
