<?php

use PHPUnit\Framework\TestCase;

class util_Test extends TestCase
{
    public function test_preserve_case_should_handle_utf_8() {
        $this->assertEquals(\i18n\util::preserve_case("åäö", "Ab"), "Åäö");
        $this->assertEquals(\i18n\util::preserve_case("Åäö", "Ab"), "Åäö");
        $this->assertEquals(\i18n\util::preserve_case("åäö", "Öb"), "Åäö");
        $this->assertEquals(\i18n\util::preserve_case("Åäö", "Öb"), "Åäö");
        $this->assertEquals(\i18n\util::preserve_case("ö",   "Ä"),  "Ö");

        $this->assertEquals(\i18n\util::preserve_case("åäö", "aa"), "åäö");
        $this->assertEquals(\i18n\util::preserve_case("Åäö", "aa"), "åäö");
        $this->assertEquals(\i18n\util::preserve_case("åäö", "a"),  "åäö");
        $this->assertEquals(\i18n\util::preserve_case("Åäö", "a"),  "åäö");
        $this->assertEquals(\i18n\util::preserve_case("Ö",   "ä"),  "ö");
    }
}