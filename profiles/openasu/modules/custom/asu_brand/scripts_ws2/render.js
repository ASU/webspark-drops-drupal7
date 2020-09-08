// Hydrate and render components with React
// {
//   title: "Degree programs",
//   text: "Degree programs",
//   href: "/",
//   items: [
//     [
//       {
//         href: "https://www.asu.edu/?feature=newsevents",
//         type: "heading",
//         text: "Column 1"
//       }, {
//         href: "https://www.asu.edu/?feature=academics",
//         target: "_top",
//         title: "Academics",
//         text: "Academics"
//       }, {
//         href: "https://www.asu.edu/?feature=research",
//         target: "_top",
//         title: "Research",
//         text: "Research"
//       }, {
//         href: "https://www.asu.edu/?feature=academics",
//         target: "_top",
//         title: "Academics",
//         text: "Academics"
//       }, {
//         href: "https://www.asu.edu/?feature=athletics",
//         target: "_top",
//         type: "button",
//         title: "Athletics",
//         text: "CTA Action 2"
//       }
//     ],
//     [
//       {
//         type: "heading",
//         text: "Column 2"
//       }, {
//         href: "https://www.asu.edu/",
//         target: "_top",
//         title: "Academics",
//         text: "Academics"
//       }, {
//         href: "https://www.asu.edu/",
//         target: "_top",
//         title: "Research",
//         text: "Research"
//       }, {
//         href: "https://www.asu.edu/?feature=athletics",
//         target: "_top",
//         title: "Athletics",
//         text: "Athletics"
//       }, {
//         href: "https://www.asu.edu/?feature=alumni",
//         target: "_top",
//         title: "Alumni",
//         text: "Alumni"
//       }, {
//         href: "https://www.asu.edu/?feature=giving",
//         target: "_top",
//         title: "Giving",
//         text: "Giving"
//       }, {
//         href: "https://www.asu.edu/?feature=president",
//         target: "_top",
//         title: "President",
//         text: "President"
//       }, {
//         href: "https://www.asu.edu/about",
//         target: "_top",
//         title: "About ASU",
//         text: "About ASU"
//       }
//     ]
//   ]
// }, {
//   title: "Students",
//   text: "My ASU",
//   href: "#",
//   target: "_top"
// }, {
//   title: "People",
//   text: "People",
//   href: "#",
//   target: "_top",
//   items: [
//     [
//       {
//         classes: "border first",
//         href: "https://www.asu.edu/map/",
//         target: "_top",
//         title: "Map",
//         text: "Map"
//       }, {
//         href: "https://campus.asu.edu/tempe/",
//         target: "_top",
//         title: "Tempe campus",
//         text: "Tempe"
//       }, {
//         href: "https://campus.asu.edu/west/",
//         target: "_top",
//         title: "West campus",
//         text: "West"
//       }, {
//         href: "https://campus.asu.edu/polytechnic/",
//         target: "_top",
//         title: "Polytechnic campus",
//         text: "Polytechnic"
//       }, {
//         href: "https://campus.asu.edu/downtown/",
//         type: "button",
//         title: "Downtown Phoenix campus",
//         text: "Downtown Phoenix"
//       }
//     ],
//     [
//       {
//         href: "https://asuonline.asu.edu/",
//         type: "heading",
//         text: "Column 2"
//       }, {
//         href: "https://havasu.asu.edu/",
//         target: "_top",
//         title: "",
//         text: "Lake Havasu"
//       }, {
//         href: "https://www.thunderbird.edu/about-thunderbird/locations/phoenix-arizona",
//         target: "_top",
//         classes: "border",
//         title: "",
//         text: "Thunderbird"
//       }, {
//         href: "https://skysong.asu.edu/",
//         target: "_top",
//         title: "",
//         text: "Skysong"
//       }, {
//         href: "https://asuresearchpark.com/",
//         target: "_top",
//         title: "",
//         text: "Research Park"
//       }, {
//         href: "https://washingtoncenter.asu.edu/",
//         target: "_top",
//         title: "",
//         text: "Washington D.C."
//       }, {
//         href: "https://wpcarey.asu.edu/mba/china-program/english/",
//         target: "_top",
//         title: "",
//         text: "China"
//       }
//     ]
//   ]
// }, {
//   title: "Research",
//   text: "Research",
//   href: "#",
//   target: "_top"
// }, {
//   title: "Apply Now",
//   text: "Apply Now",
//   type: "button",
//   color: "gold",
//   href: "https://admissions.asu.edu",
//   target: "_top"
// }, {
//   title: "CTA Button",
//   text: "CTA Button",
//   type: "button",
//   color: "maroon",
//   href: "https://asu.edu",
//   target: "_top"
// }

(function ($) {
  Drupal.behaviors.asu_brand = {
    attach: function (context, settings) {
        var NavTree = [
          {
            "href": "\/",
            "title": "Home",
          }
        ];

        console.log(JSON.parse(Drupal.settings.asu_brand.navTree));

        AsuWebcore.RenderPreact(AsuWebcore.Header, {
          navTree: JSON.parse(Drupal.settings.asu_brand.navTree),
          title: Drupal.settings.asu_brand.siteSubtitle,
          subtitle: Drupal.settings.asu_brand.siteName
        }, document.getElementById("headerContainer"));
    }
  };
}(jQuery));
