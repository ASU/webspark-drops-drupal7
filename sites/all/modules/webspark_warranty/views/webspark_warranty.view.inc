<?php

/**
 * Page callback for /reports/warranty.
 */
function webspark_warranty_status_page()
{
  $warrantyMessage = "";
  $status = webspark_warranty_get_warranty_status();

  if ($status == 'True')
    $warrantyMessage .= '<h1>Current Status: <span style="color: green">In Warranty</span></h1>';
  else
  {
    $unsupportedModules = webspark_warranty_get_unsupported_modules();

    $warrantyMessage .= '<h1>Current Status: <span style="color: red">Out of Warranty</span></h1>';
    $warrantyMessage .= '<h2> The following modules / themes are not covered by the Webspark Warranty: </h2>';

    $moduleList = '<table class="table">
                          <thead>
                            <tr>
                              <th>Name</th>
                              <th>Type</th>
                            </tr>
                          </thead>
                          <tbody>';

    foreach ($unsupportedModules as $unsupportedModule)
    {
      $moduleList .= '<tr>
        <td>' . $unsupportedModule["name"] . '</td>
        <td>' . $unsupportedModule["type"] . '</td>
      </tr>';
    }
    $moduleList .= '</tbody>
                        </table>';

    $warrantyMessage .= $moduleList;
  }

  return '<div> ' . $warrantyMessage . '</div>';
}
