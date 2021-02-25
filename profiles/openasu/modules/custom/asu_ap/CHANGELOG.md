### ASU Academic Programs 7.x-3.2, 2021-02-24
- Added unique classes to the gold RFI buttons in ASU AP pages for analytics tracking
- Incorporated SASS into theming
- Added styling to degree description elements
- Added the following campuses to campus lists:
  - ASU@Los Angeles
  - ASU@Northeastern Arizona

### ASU Academic Programs 7.x-3.1, 2020-05-15
- The ASU@Lake Havasu campus link now works
- Certain ASUOnline links URLs now correctly point to asuonline.asu.edu resources instead of Degree
  Search pages
- The ASUOnline FAQ information at the bottom of degree pages has been updated

### ASU Academic Programs 7.x-3.0, 2020-04-07
##### Architecture & Development
- Reformatted page-level TPL file output (code and HTML)
- Combined graduate vs. undergrad logic in TPL
- Added new fields to ASU AP degree page content type to store additional
  data to render on degree pages.
- Added many other Degree Search field mapping options for
  future additional fields, if needed
- Re-added missing "asu_feeds_text_format" Drupal input format
- Campus options updated to current list
- Added configuration form to handle new, optional elements of degree pages
  pulled in from Degree Search that can be toggled on/off:
    - The visibility of degree page fields with data imported from Degree
      Search data
    - Showing/hiding of marketing video content at top of degree pages
- Refactored ASU AP CSS
    - Namespaced existing selectors
    - Removed duplicate rules
    - Added CSS for new elements
##### Bug fixes
- Updated ASU IXR library or PHP 7.x compatibility
##### UI/UX Improvements
- Degree pages:
    - Added canonical URLs in <link> tags pointing at Degree Search page counterparts for SEO improvements
    - Added marketing text and video pulled in from Degree Search and logic to determine when to show them
    - Added several newer Degree Search pages elements to individual degree page output middle section
    - Online campus link now point to the corresponding asuonline.asu.edu degree page
    - Added missing and/or new degree "special categories" links to title banner
    - Special category text now link to explanations (imported from Degree Search) optionally rendered at the bottom of the page.
- Updated casing to "Sentence casing" (vs. Title Casing)
- Degree page edit form explanatory messaging improved
- Fixed @media rules for better tablet layouts


### ASU Academic Programs 7.x-2.5, 2019-08-02
- Codified and unified CSS value for ASU gold to #fffc732

### ASU Academic Programs 7.x-2.4, 2019-01-17
- Fix related programs field display on program nodes and node edit forms
- Fix misaligned/missing breadcrumbs on program nodes
- Fix truncated Views exposed filter text
- Add Yavapai, Pima and Cochise campus support
- Fix data importing for college/department joint programs
- Fix Views grid display on program overview grid pages

### ASU Academic Programs 7.x-2.3, 2018-05-23
- Add changelog to module

### ASU Academic Programs 7.x-2.2, 2018-04-18
- Add necessary styling back to degrees 'Example Careers' section

### ASU Academic Programs 7.x-2.1, 2017-12-22
- Updated the ASU Academic Programs README.md with improved markdown styling
- Updated asu-drupal-modules README.md with more accurate information
- Updated comments for ASU Academic Programs
- Added College of Law, SFIS, Thunderbird school and campus to importing options; updated PUBSRV's college display name
- Added support for joint ownership of programs
- Better module comments for ASU Academic Programs Node edit form - Hid new joint fields (replaced original fields)
- Added behavior to hide "People >" filter selection breadcrumb when no filters are shown
- Updated the ASU Academic Programs README.md with better markdown styling
- Updated asu-drupal-modules README.md with more accurate information

### ASU Academic Programs 7.x-2.0, 2017-08-27
- Initial release of the ASU Academic Programs module
- Deprecated ASU Degrees module
