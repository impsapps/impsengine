
module.exports = {

    name: "ImpsApps Class Template",

    directory: true,

    params: ["ClassName"],

    rules: function(config) {

      return({
        items: [
          { destinationFile: config.ClassName + ".h",           sourceTemplateFile: "TEMPLATE.h"    },
          { destinationFile: config.ClassName + ".c",           sourceTemplateFile: "TEMPLATE.c"    }
        ]
      });

    }

}
