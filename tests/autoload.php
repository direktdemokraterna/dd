<?php
spl_autoload_register(
    function($class) {
        static $classes = null;
        if ($classes === null) {
            $classes = array(
                'general_helpers' => '/../src/web/helpers/general_helpers.inc',
                'i18n\\util' => '/../src/web/helpers/i18n/util.inc'
            );
        }
        $cn = strtolower($class);
        if (isset($classes[$cn])) {
            require __DIR__ . $classes[$cn];
        }
    },
    true,
    false
);