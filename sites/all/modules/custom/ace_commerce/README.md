ACE Commerce module

-----------------------------

Before enabling this module: 

1) Import the following Rules Components at /admin/config/workflow/rules/components

- A Product Is Cyber

`
{ "rules_is_cyber_product" : {
    "LABEL" : "A Product Is Cyber",
    "PLUGIN" : "or",
    "OWNER" : "rules",
    "TAGS" : [ "Commerce Product" ],
    "REQUIRES" : [ "ace_commerce" ],
    "USES VARIABLES" : {
      "new_product" : { "label" : "Product", "type" : "commerce_product" },
      "product_type" : { "label" : "Product Types", "type" : "list\u003Ctext\u003E" }
    },
    "OR" : [
      { "commerce_product_selected_product_type" : {
          "new_product" : [ "new_product" ],
          "product_type" : { "value" : {
              "annual_golf_tournament" : "annual_golf_tournament",
              "annual_networking_reception" : "annual_networking_reception",
              "innovation_think_tank_product" : "innovation_think_tank_product",
              "membership_entity_product" : "membership_entity_product"
            }
          }
        }
      }
    ]
  }
}
`

- Are Products of Type

`
{ "rules_are_products_of_type" : {
    "LABEL" : "Are Products of Type",
    "PLUGIN" : "or",
    "OWNER" : "rules",
    "TAGS" : [ "Commerce Order" ],
    "REQUIRES" : [ "commerce_order" ],
    "USES VARIABLES" : { "commerce_order" : { "label" : "Order", "type" : "commerce_order" } },
    "OR" : [
      { "commerce_order_contains_product_type" : {
          "commerce_order" : [ "commerce_order" ],
          "product_type" : { "value" : {
              "annual_golf_tournament" : "annual_golf_tournament",
              "annual_networking_reception" : "annual_networking_reception",
              "innovation_think_tank_product" : "innovation_think_tank_product",
              "membership_entity_product" : "membership_entity_product"
            }
          },
          "operator" : "\u003E=",
          "value" : "1"
        }
      }
    ]
  }
}
`

2) Make sure the Product Types selections in the "Order contains products of particular product types" condition in the "CyberSource Secure Acceptance Web/Mobile" Rule matches in both of the Components above.
