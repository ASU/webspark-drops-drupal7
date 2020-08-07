This theme starter kit is meant to act as a guide when setting up your own custom theme directory to zip, and upload for use in OpenScholar. For first time themers, it is recommended that this starterkit directory be used as the basis for the custom theme--it will help lessen the chances of forgetting to include a file or a reference somewhere. Again, this is only a suggestion. 

While having Drupal theming experience is not necessary to create a custom theme, being comfortable with writing CSS and using Firebug or Chrome Dev Tools are important skills to have. The key to successful Drupal theming is understanding how the many layers of css affect various html elements, and knowing how to override only the css rules and/or attributes that are required to attain the desired styled result, in the custom theme. Using Firebug or Chrome Dev Tools will indicate exactly which css rules/attributes need to be overridden in the custom theme css file(s).  
**************************************************

* Before adding styles or javascript to a css or js file, all instances of starterkit should be replaced with the name of the custom theme. Replacing instances of this name includes the names of the css files found in this kit, references to css file(s) or a js file in the .flav file (same type of file as an .info, but used for sub/sub themes), and the name of this parent directory. 

* Once all instances of starterkit have been replaced with the name of the custom theme, start by opening the .flav file. This file is critical in order for the custom theme to work. 

* As noted in the .flav file, all lines beginning with a semicolon are commented out and will not be read by the system.  To use one of these directives, you'll have to uncomment it be removing the leading semicolon.  

* First, you will need to select an existing OpenScholar theme to base your subtheme on.  This theme will be your starting point and all the changes you make will modify that.  To select a parent theme, change the `module` line in your .flav file.  The system names of OpenScholar's themes are aberdeen, aglet, airstream, ballard, bartik, bigpic, bunchy, cayley, cleanblue, collector, collegiate, commodore, department, documental, dunster, eloquent, garland, hwpi_classic, hwpi_modern, hwpi_vibrant, nortony, redhead, seven, stark, stripy, and weft.

* Once all of the references in the .flav file have been updated and/or uncommented/activated, adding css rules and attributes to the css file can begin. 

* After updating the files, commit them to your own github fork or create a .zip file.  The files in the starter kit must be at the top level of your zip file, not buried in a directory.


**************************************************

As mentioned above, using Firebug or Chrome Dev tools to "pick through" the markup will identify which elements need over-riding. As a workflow suggestion, its easier to start with the outer elements in the DOM--things like the body tag, the page div, the menu-bar div, etc. Once these outer elements have been styled, more specific styling can be applied to things like the main menu li's, block h2's, various widget list styles found in the sidebar regions, etc. 






