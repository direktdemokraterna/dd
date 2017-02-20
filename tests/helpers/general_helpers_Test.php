<?php

use PHPUnit\Framework\TestCase;

class General_helpers_Test extends TestCase
{
    public function test_check_personnummer_should_return_true_when_valid_personal_identity_number() {
        $this->assertTrue(general_helpers::check_personnummer("2121010108"));
        $this->assertTrue(general_helpers::check_personnummer("212101-0108"));
        $this->assertTrue(general_helpers::check_personnummer("192121010108"));
        $this->assertTrue(general_helpers::check_personnummer("200121010102"));
        $this->assertTrue(general_helpers::check_personnummer("20012101-0102"));
    }

    public function test_check_personnummer_should_return_false_when_invalid_personal_identity_number() {
        $this->assertFalse(general_helpers::check_personnummer("0101010101"));
        $this->assertFalse(general_helpers::check_personnummer(null));
        // the check does not check if it's a valid date.
        // $this->assertFalse(general_helpers::check_personnummer("0000000000"));
    }

    public function test_clean_personnummer_should_return_12_digits() {
        $this->assertEquals("200101010101", general_helpers::clean_personnummer("0101010101"));
        $this->assertEquals("201101010102", general_helpers::clean_personnummer("1101010102"));
        $this->assertEquals("192121010108", general_helpers::clean_personnummer("2121010108"));

        $this->assertEquals("200101010101", general_helpers::clean_personnummer("010101-0101"));
        $this->assertEquals("192121010108", general_helpers::clean_personnummer("192121010108"));
    }


}